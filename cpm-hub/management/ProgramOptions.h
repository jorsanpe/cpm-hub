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
#include <http/http.h>

struct ProgramOptions {
    enum AuthenticatorType {
        UNAUTHENTICATED,
        ACCESS_FILE_AUTHENTICATOR,
        CPM_HUB_AUTHENTICATOR,
    };

    enum KpiSinkType {
        NO_KPIS,
        INFLUXDB,
    };

    enum BitsRepositoryType {
        BITS_REPOSITORY_FILESYSTEM,
        BITS_REPOSITORY_SQLITE,
    };

    BitsRepositoryType bits_repository_type = BITS_REPOSITORY_FILESYSTEM;
    std::string bits_directory = ".";
    std::string sqlite_database = "bits.db";
    AuthenticatorType authenticator_type = UNAUTHENTICATED;
    std::string access_file = ".access";
    std::string cpm_hub_url = "http://localhost:1234";
    std::string http_service_ip = "127.0.0.1";
    int http_service_port = 8000;
    std::string http_management_ip = "127.0.0.1";
    int http_management_port = 8001;
    HttpSecurityOptions security_options;

    std::string logger_file;
    int logger_max_file_size;
    int logger_max_files;

    KpiSinkType kpi_sink = NO_KPIS;
    std::string influxdb_db = "mydb";
    std::string influxdb_url = "http://localhost:1234";
};
