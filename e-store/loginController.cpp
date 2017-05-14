//
//  loginController.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "loginController.hpp"
#include "user.hpp"
#include "systemUI.hpp"
#include <fstream>
#include <cctype>
#include <algorithm>
#include <string>

std::string getAttr(int n, std::string line) {
    const char SEPCHR = ' ';
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
    return parsed;
}


bool LoginController::get(User &usr) {
    
    std::string name;
    std::cin >> name;
    std::cout << "password: ";
    std::string password;
    std::cin >> password;
    
//    std::ofstream ofile("b.txt");
//    ofile << "AVasK 7997 admin\n";
//    ofile << "gman 0000 operator";
//    ofile.close();
    
    std::string filename = "b.txt";
    std::string line;
    std::ifstream infile(filename);
    bool match = false;
    auto access_lvl = OPERATOR;
    while (std::getline(infile, line)) {
        std::cout << line << " <-line \n";
        std::string fname, fpass, fpost;
        fname = getAttr(1, line);
        fpass = getAttr(2, line);
        fpost = getAttr(3, line);
        std::transform(fpost.begin(), fpost.end(), fpost.begin(), ::tolower); //converting to lower-case
        
        // DEBUG INFO : ______________________________________
        //        std::cout << "\"" << fname << "\" - name\n";
        //        std::cout << "\"" << fpass << "\" - pass\n";
        //        std::cout << "\"" << fpost << "\" - post\n";
        
        if ((fname == name) && (fpass == password)) {
            match = true;
            if (fpost == "operator")
                access_lvl = OPERATOR;
            else if (fpost == "admin")
                access_lvl = ADMIN;
            else
                match = false;
        }
    }
    infile.close();
    
    if (match) { usr.setName(name); usr.setAccessLvl(access_lvl); return true; }
    //if (name == "gman") { usr.setName(name); usr.setAccessLvl(OPERATOR); return true; }
    //if (name != "AVasK") { return false; }
    return false;
}


