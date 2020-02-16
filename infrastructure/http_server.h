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
#pragma once

#include <functional>
#include <map>
#include <string>
#include <thread>
#include <mongoose/mongoose.h>
#include <infrastructure/http.h>

typedef std::function<struct http_response(struct http_request)> ServerCallback;

class HttpServer {
public:
    struct mg_serve_http_opts options;

    void get(std::string path, ServerCallback callback);
    void post(std::string path, ServerCallback callback);
    void start(int port);
    void stop();
    void serveRequest(struct mg_connection *connection, struct http_message *message);

private:
    int port;
    bool running;
    struct mg_mgr mgr;
    struct mg_connection *connection;
    std::thread *server_thread;
    std::map<std::string, ServerCallback> gets;
    std::map<std::string, ServerCallback> posts;

    void serve();
    ServerCallback findCallback(std::string method, std::string endpoint);
};
