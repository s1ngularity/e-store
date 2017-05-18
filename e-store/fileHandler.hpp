//
//  fileHandler.hpp
//  e-store
//
//  Created by Alex Vaskov on 14.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef fileHandler_hpp
#define fileHandler_hpp

#include <iostream>
#include <vector>

class FileHandler {
    std::string filename = "none";
public:
    FileHandler() {}
    FileHandler(std::string file) : filename(file) {}
    void appendToFile(std::string line);
    void setDestFile(std::string file);
    std::vector<std::string> getLines();
};


class FileHandlerException {
    std::string error;
public:
    FileHandlerException(std::string err) : error(err) {}
};

#endif /* fileHandler_hpp */
