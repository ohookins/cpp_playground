//
//  ContentfulClient.cpp
//  Contentful.cpp
//
//  Created by Oliver Hookins on 16.01.18.
//  Copyright © 2018 Oliver Hookins. All rights reserved.
//

#include "ContentfulClient.hpp"
#include <iostream>
#include <cassert>

ContentfulClient::ContentfulClient(std::string TokenToSet)
{
    CurlHandle = curl_easy_init();
    assert(CurlHandle);
    
    Token = TokenToSet;
    std::cout << "Created the client" << std::endl;
}

void ContentfulClient::GetEntries(std::string Space)
{
    // Prepare the authorised URL
    // TODO: Should it be escaped?
    std::string URL = CDA + "/spaces/" + Space + "/entries?access_token=" + Token;
    
    // Set the URL, write callback and perform the request
    curl_easy_setopt(CurlHandle, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(CurlHandle, CURLOPT_ERRORBUFFER, &ErrorData);
    curl_easy_setopt(CurlHandle, CURLOPT_HEADERDATA, HeaderData);
    curl_easy_setopt(CurlHandle, CURLOPT_WRITEDATA, BodyData);
    auto res = curl_easy_perform(CurlHandle);
    
    // Check that the request succeeded
    if (res != CURLE_OK) {
        std::cout << "CDA entries request failed" << std::endl;
        std::cout << ErrorData << std::endl;
        curl_easy_cleanup(CurlHandle);
        return;
    }

    // Print out data
//    std::cout << HeaderData << std::endl;
//    std::cout << BodyData << std::endl;
    
    // Cleanup the handle and allocated things
    curl_easy_cleanup(CurlHandle);
//    free(HeaderData);
//    free(BodyData);
//    free(CurlHandle);
}
