//
//  parser.cpp
//  e-store
//
//  Created by Alex Vaskov on 14.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "parser.hpp"

std::string Parser::getAttr(int n, std::string line) { // ADD: throw exception
    n--;
    std::string parsed = "";
    for (int i = 0; i < line.size(); i++) {
        if (n < 0) {
            break;
        }
        if (line[i] == SEPCHR) {
            n--;
        }
        else if (n == 0) {
            parsed += line[i];
        }
    }
    if (n > 0) {
        throw ParseException("not enough parameters");
    }
    return parsed;
}

void Parser::setSepChar(char ch) {
    SEPCHR = ch;
}
