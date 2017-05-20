//
//  fileHandler.cpp
//  e-store
//
//  Created by Alex Vaskov on 14.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "fileHandler.hpp"
#include <iostream>
#include <fstream>
#include <string>

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

std::vector<std::string> FileHandler::getLines() {
    std::ifstream infile(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    return lines;
}

void FileHandler::rewriteFile(std::string line) {
    std::ofstream ofile(filename);
    ofile << line;
    ofile.close();
}

void FileHandler::rewriteFile(std::vector<std::string> lines) {
    std::ofstream ofile(filename);
    for (auto line : lines) {
        ofile << line << "\n";
    }
    ofile.close();
}


bool FileHandler::fileExists(std::string fname) {
    if (std::ifstream(fname))
    {
        //File exists
        return true;
    }
    // File doesn't exist
    return false;
}
