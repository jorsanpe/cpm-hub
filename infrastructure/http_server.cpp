/*
 * Copyright (C) 2020  Jordi Sánchez
 * This file is part of CPM Hub
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <sstream>

#include <infrastructure/http_server.h>

using namespace std;

static void eventHandler(struct mg_connection *connection, int event, void *data);


void HttpServer::start(int port)
{
    ostringstream string_stream;

    string_stream << "127.0.0.1:" << port;

    cout << "Started server on " << string_stream.str() << endl;

    this->port = port;
    this->running = true;
    mg_mgr_init(&mgr, this);
    connection = mg_bind(&mgr, string_stream.str().c_str(), eventHandler);
    mg_set_protocol_http_websocket(connection);

    this->server_thread = new thread(&HttpServer::serve, this);
}


void HttpServer::stop()
{
    this->running = false;
    this->server_thread->join();
    mg_mgr_free(&mgr);
}


void HttpServer::serve()
{
    while (this->running) {
        mg_mgr_poll(&mgr, 100);
    }
}


void HttpServer::post(string path, ServerCallback callback)
{
    this->posts.insert(make_pair(path, callback));
}


void HttpServer::get(string path, ServerCallback callback)
{
    this->gets.insert(make_pair(path, callback));
}


void HttpServer::put(string path, ServerCallback callback)
{
    this->puts.insert(make_pair(path, callback));
}


static struct http_response notFound(struct http_request request)
{
    return http_response(404, "");
}


ServerCallback HttpServer::findCallback(string method, string endpoint)
{
    map<string, ServerCallback> *callbacks;

    if (method == "GET") {
        callbacks = &this->gets;
    } else if (method == "POST") {
        callbacks = &this->posts;
    } else if (method == "PUT") {
        callbacks = &this->puts;
    }

    auto iter = callbacks->find(endpoint);

    if (iter == callbacks->end()) {
        return notFound;
    }

    return iter->second;
}


void HttpServer::serveRequest(struct mg_connection *connection, struct http_message *message)
{
    struct http_response response;
    struct http_request request(string(message->body.p, message->body.len));
    string method(message->method.p, message->method.len);
    string endpoint(message->uri.p, message->uri.len);
    ServerCallback callback = this->findCallback(method, endpoint);

    response = callback(request);

    mg_send_head(connection, response.status_code, response.body.size(), "");
    mg_printf(connection, "%s", response.body.c_str());

    cout << method << " " << endpoint << ": " << response.status_code << endl;
}


static void eventHandler(struct mg_connection *connection, int event, void *data)
{
    HttpServer *server = (HttpServer *)connection->mgr->user_data;
    struct http_message *message = (struct http_message *)data;

    switch (event) {
    case MG_EV_HTTP_REQUEST:
        server->serveRequest(connection, message);
        break;

    default:
        break;
    }
}
