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
#include <cest/cest.h>

#include <api/plugins_api.h>
#include <infrastructure/plugins_repository_in_memory.h>

using namespace cest;


describe("CPM Hub registers plugins", []() {
    beforeEach([&]() {
    });

    afterEach([&]() {
    });

    it("registers a plugin", [&]() {
        struct http_request request("{"
            "\"plugin_name\": \"cest\","
            "\"file_name\": \"cest.zip\","
            "\"payload\": \"ABCDEabcde\""
        "}");
        struct http_response response;
        PluginsRepositoryInMemory repository;
        PluginsService service(&repository);
        PluginsApi api(&service);

        response = api.publishPlugin(request);

        expect(response.status_code).toBe(200);
        expect(response.body).toBe("");
    });

    it("lists a plugin after it has been registered", [&]() {
        struct http_request request("{"
            "\"plugin_name\": \"cest\","
            "\"file_name\": \"cest.zip\","
            "\"payload\": \"ABCDEabcde\""
        "}");
        struct http_response response;
        PluginsRepositoryInMemory repository;
        PluginsService service(&repository);
        PluginsApi api(&service);

        api.publishPlugin(request);

        response = api.listPlugins(request);

        expect(response.status_code).toBe(200);
        expect(response.body).toBe("[{\"plugin_name\":\"cest\"}]");
    });
});