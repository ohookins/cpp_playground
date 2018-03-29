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
#include "cpr/cpr.h"
#include "json.hpp"

using json = nlohmann::json;

ContentfulClient::ContentfulClient(std::string TokenToSet)
{
    Token = TokenToSet;
    std::cout << "Created the client" << std::endl;
}

void ContentfulClient::GetEntries(std::string Space)
{
    // Prepare the authorised URL
    // TODO: Should it be escaped?
    std::string URL = CDA + "/spaces/" + Space + "/entries?access_token=" + Token;
    
    // Set the URL and perform the request
    auto r = cpr::Get(cpr::Url{URL});
    
    // Basic error checking
    if (!(r.status_code == 200) || !(r.header["content-type"] == "application/vnd.contentful.delivery.v1+json"))
    {
        std::cout << "Unexpected response." << std::endl;
        std::cout << "Status: " << r.status_code << std::endl;
        std::cout << "Content-Type: " << r.header["content-type"] << std::endl;
        return;
    }
    
    json Body = json::parse(r.text);
    std::cout << "Item count: " << Body["items"].size() << std::endl;
}
