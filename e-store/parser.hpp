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

class ParseException {
    std::string about;
public:
    ParseException() : about("untitled exception") {}
    ParseException(std::string t_name) : about(t_name) {}
    std::string what() { return about; }
    
};

#endif /* parser_hpp */
