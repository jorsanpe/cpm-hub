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

#include <vector>
#include <string>
#include <infrastructure/clock.h>


#define INFO(...)       logger->info(__VA_ARGS__)
#define WARN(...)       logger->warn(__VA_ARGS__)
#define ERROR(...)      logger->error(__VA_ARGS__)


struct LogMessage {
    TimeMs time;
    enum {
        LOG_SEVERITY_INFO,
        LOG_SEVERITY_WARNING,
        LOG_SEVERITY_ERROR,
    } severity;
    const char *message;
};


class Logger {
public:
    virtual void info(const char *message, ...) = 0;
    virtual void warn(const char *message, ...) = 0;
    virtual void error(const char *message, ...) = 0;
};


extern Logger *logger;
