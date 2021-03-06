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

#include <string>
#include <http/HttpParameterMap.h>


struct HttpRequest {
    std::string path;
    std::string method;
    std::string body;
    std::string protocol;
    std::string client_ip;
    struct HttpParameterMap query_parameters;
    struct HttpParameterMap parameters;
    struct HttpParameterMap headers;

    HttpRequest(std::string _body="") {
        body = _body;
    }

    void withHeader(const std::string &name, const std::string &value) {
        headers.set(name, value);
    }
};
