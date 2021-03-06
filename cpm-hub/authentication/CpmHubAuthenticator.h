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
#include <authentication/Authenticator.h>
#include <http/HttpClient.h>


class CpmHubAuthenticator : public Authenticator {

public:
    CpmHubAuthenticator(const std::string &auth_service_url, HttpClient &client);

    virtual Maybe<std::string> authenticate(const char *key) override;

    virtual bool validCredentials(UserCredentials &credentials) override;

    virtual void addUser(UserCredentials &credentials);

    virtual void addUserWithInvitation(UserCredentials &credentials, std::string invitation_token);

private:
    std::string authentication_endpoint;
    std::string users_endpoint;
    HttpClient *client;
};
