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

class Template {
public:
    Template() : Template("") {
    }

    Template(const std::string &name) {
        this->name = name;
        this->version = "";
        this->username = "";
        this->payload = "";
    }

    Template(const std::string &name, const std::string &version) {
        this->name = name;
        this->version = version;
        this->username = "";
        this->payload = "";
    }

    Template(const std::string &name, const std::string &version, const std::string &username, const std::string &payload) {
        this->name = name;
        this->version = version;
        this->username = username;
        this->payload = payload;
    }

    std::string name;
    std::string version;
    std::string username;
    std::string payload;
};