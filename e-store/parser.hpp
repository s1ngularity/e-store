//
//  parser.hpp
//  e-store
//
//  Created by Alex Vaskov on 14.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>

class Parser {
    char SEPCHR = ' ';
public:
    std::string getAttr(int, std::string);
    void setSepChar(char);
};

#endif /* parser_hpp */
