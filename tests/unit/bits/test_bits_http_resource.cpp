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
#include <fakeit/fakeit.hpp>

#include <list>
#include <bits/rest_api/BitsHttpResource.h>
#include <bits/BitsService.h>

using namespace cest;
using namespace fakeit;
using namespace std;

HttpRequest post_request_with_invalid_bit_name(
"{"
    "\"bit_name\": \"cest'; DELETE * from bits;\","
    "\"version\": \"1.0\","
    "\"payload\": \"ABCD\","
    "\"username\": \"johndoe\","
    "\"password\": \"pass\""
"}");

HttpRequest post_request_with_invalid_version(
"{"
    "\"bit_name\": \"cest\","
    "\"version\": \"dd 1.0\","
    "\"payload\": \"ABCD\","
    "\"username\": \"johndoe\","
    "\"password\": \"pass\""
"}");

HttpRequest post_request_with_invalid_username(
"{"
    "\"bit_name\": \"cest'; DELETE * from bits;\","
    "\"version\": \"dd 1.0\","
    "\"payload\": \"ABCD\","
    "\"username\": \"john} doe\","
    "\"password\": \"pass\""
"}");

HttpRequest post_request_with_invalid_payload(
"{"
    "\"bit_name\": \"cest'; DELETE * from bits;\","
    "\"version\": \"dd 1.0\","
    "\"payload\": \"ABCD !;Eabcde\","
    "\"username\": \"john} doe\","
    "\"password\": \"pass\""
"}");


describe("Bits API", []() {
    it("uses the bit service to publish a bit", [&]() {
        HttpRequest request("{"
            "\"bit_name\": \"cest\","
            "\"version\": \"1.0\","
            "\"payload\": \"ABCDEabcde\","
            "\"username\": \"john_doe\","
            "\"password\": \"pass\""
        "}");
        HttpResponse response;
        Bit bit("");
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());

        When(Method(mock_service, publishBit)).Return(bit);
        When(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string, string))).Return(Maybe<Bit>());

        response = api.post(request);

        expect(response.status_code).toBe(200);
        expect(response.body).toBe("");
        Verify(Method(mock_service, publishBit).Matching([](struct BitPublicationData data) {
            return data.bit_name == "cest" &&
                   data.version == "1.0" &&
                   data.user_name == "john_doe" &&
                   data.payload == "ABCDEabcde";
        }));
    });

    it("returns status code 400 when request contains invalid fields", [&]() {
        HttpResponse response;
        Bit bit("");
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());

        expect(api.post(post_request_with_invalid_bit_name).status_code).toBe(400);
        expect(api.post(post_request_with_invalid_version).status_code).toBe(400);
        expect(api.post(post_request_with_invalid_username).status_code).toBe(400);
        expect(api.post(post_request_with_invalid_payload).status_code).toBe(400);
    });

    it("returns error 401 when publishing a bit and authentication fails", [&]() {
        HttpRequest request("{"
            "\"bit_name\": \"cest\","
            "\"version\": \"1.0\","
            "\"payload\": \"ABCDEabcde\","
            "\"username\": \"john_doe\","
            "\"password\": \"pass\""
        "}");
        HttpResponse response;
        Mock<BitsService> mock_service;
        Mock<Authenticator> mock_authenticator;
        BitsHttpResource api(&mock_service.get(), &mock_authenticator.get());

        When(Method(mock_authenticator, validCredentials)).Return(false);

        response = api.post(request);

        expect(response.status_code).toBe(HttpStatus::UNAUTHORIZED);
    });

    it("returns error 409 when publishing a bit and version already exists", [&]() {
        HttpRequest request("{"
                            "\"bit_name\": \"cest\","
                            "\"version\": \"1.0\","
                            "\"payload\": \"ABCDEabcde\","
                            "\"username\": \"john_doe\","
                            "\"password\": \"pass\""
                            "}");
        HttpResponse response;
        Mock<BitsService> mock_service;
        Mock<Authenticator> mock_authenticator;
        BitsHttpResource api(&mock_service.get(), &mock_authenticator.get());
        Maybe<Bit> cest_bit;

        request.parameters.set("bitName", "cest");
        cest_bit = Bit("cest", "1.0", "user", "ABCDEabcde");

        When(Method(mock_authenticator, validCredentials)).Return(true);
        When(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string, string))).Return(cest_bit);

        response = api.post(request);

        expect(response.status_code).toBe(HttpStatus::CONFLICT);
    });
        
    it("returns error 404 when downloading a bit that is not found", [&]() {
        HttpRequest request;
        HttpResponse response;
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());
        Maybe<Bit> no_bit;

        request.parameters.set("bitName", "cest");
        When(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string))).Return(no_bit);

        response = api.get(request);

        Verify(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string)).Using("cest"));
        expect(response.status_code).toBe(404);
    });
            
    it("returns latest bit version when downloading an existing bit", [&]() {
        HttpRequest request;
        HttpResponse response;
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());
        Maybe<Bit> cest_bit;

        request.parameters.set("bitName", "cest");
        cest_bit = Bit("cest", "1.0", "user", "ABCDEabcde");
        When(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string))).Return(cest_bit);

        response = api.get(request);

        Verify(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string)).Using("cest"));
        expect(response.status_code).toBe(200);
        expect(response.body).toBe("{"
            "\"bit_name\":\"cest\","
            "\"payload\":\"ABCDEabcde\","
            "\"version\":\"1.0\""
        "}");
    });

    it("returns specific bit version when downloading an existing bit", [&]() {
        HttpRequest request;
        HttpResponse response;
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());
        Maybe<Bit> cest_bit;

        request.parameters.set("bitName", "cest");
        request.parameters.set("bitVersion", "1.1");
        cest_bit = Bit("cest", "1.1", "user", "ABCDEabcde");
        When(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string, string))).Return(cest_bit);

        response = api.get(request);

        Verify(OverloadedMethod(mock_service, bitBy, Maybe<Bit>(string, string)).Using("cest", "1.1"));
        expect(response.status_code).toBe(200);
        expect(response.body).toBe("{"
           "\"bit_name\":\"cest\","
           "\"payload\":\"ABCDEabcde\","
           "\"version\":\"1.1\""
        "}");
    });

    it("uses the bit service to search for bits based on given criteria", [&]() {
        HttpRequest request;
        HttpResponse response;
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());
        std::list<BitMetadata> one_bit_found = {
            BitMetadata("cest", "pepe", "1.0"),
        };

        request.query_parameters.set("name", "cest");
        When(Method(mock_service, search)).Return(one_bit_found);

        response = api.get(request);

        expect(response.status_code).toBe(HttpStatus::OK);
        Verify(Method(mock_service, search).Matching([](BitSearchQuery search_query) {
            return search_query.name == "cest";
        }));
        expect(response.body).toBe("[{\"author\":\"pepe\",\"name\":\"cest\"}]");
    });

    it("returns bad request when search query does not contain 'name' parameter", [&]() {
        HttpRequest request;
        HttpResponse response;
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());

        response = api.get(request);

        expect(response.status_code).toBe(HttpStatus::BAD_REQUEST);
    });

    it("returns bad request when 'name' parameter in search query is empty", [&]() {
        HttpRequest request;
        HttpResponse response;
        Mock<BitsService> mock_service;
        BitsHttpResource api(&mock_service.get());

        request.query_parameters.set("name", "");
        response = api.get(request);

        expect(response.status_code).toBe(HttpStatus::BAD_REQUEST);
    });
});
