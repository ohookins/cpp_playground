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
    auto client = ContentfulClient("796733cd79dbbfcba82941f0896c664f0930d2623d99cd2e39ae4bdc97a1b409");
    client.GetEntries("m20artr3xszm");
    
    return 0;
}
