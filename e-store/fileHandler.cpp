//
//  fileHandler.cpp
//  e-store
//
//  Created by Alex Vaskov on 14.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "fileHandler.hpp"
#include <fstream>


void FileHandler::setDestFile(std::string file) {
    filename = file;
}

void FileHandler::appendToFile(std::string line) {
    if (this->filename == "none") {
        throw FileHandlerException("no file chosen!");
    }
    std::ofstream ofile;
    ofile.open(this->filename, std::ios_base::app);
    ofile << line;
    ofile.close();
}
