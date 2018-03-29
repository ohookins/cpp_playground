//
//  main.cpp
//  Contentful.cpp
//
//  Created by Oliver Hookins on 16.01.18.
//  Copyright © 2018 Oliver Hookins. All rights reserved.
//

#include <iostream>
#include "ContentfulClient.hpp"

int main(int argc, const char * argv[]) {
    auto client = ContentfulClient("API_KEY");
    client.GetEntries("SPACE_ID");
    
    return 0;
}
