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

#include <authentication/Authenticator.h>
#include <bits/BitsService.h>
#include <authentication/UserCredentials.h>
#include <http/HttpResource.h>

class BitsHttpResource: public HttpResource {
public:
    BitsHttpResource(BitsService *bits_service);

    BitsHttpResource(BitsService *bits_service, Authenticator *authenticator);

    HttpResponse post(HttpRequest &request);

    HttpResponse get(HttpRequest &request);

    HttpResponse listBits(HttpRequest &request);

private:
    BitsService *bits_service;

    Authenticator *authenticator;

    HttpResponse searchForBit(HttpRequest &request);

    HttpResponse getBit(HttpRequest &request);

    bool isValidPublicationData(BitPublicationData &publication_data);
};
