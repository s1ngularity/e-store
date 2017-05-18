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
#include "fileHandler.hpp"
#include <fstream>
#include <cctype>
#include <algorithm>
#include <string>

std::string filename = "b.txt";

void LoginController::add(const User &usr, std::string password) {
    FileHandler filehandler(filename);
    std::string usr_data = "";
    usr_data = usr.getName() + " " + password + " " + ((usr.getAccessLvl() == ADMIN) ? "admin" : "operator") + "\n";
    filehandler.appendToFile(usr_data);
}

void LoginController::del(std::string name) {
    
}

User *LoginController::get() {
    User *usrptr;
    usrptr = new User;
    Parser parser;
    parser.setSepChar(' ');
    
    std::string name;
    std::cin >> name;
    std::cout << "password: ";
    std::string password;
    std::cin >> password;
    
//    std::ofstream ofile("b.txt");
//    ofile << "AVasK 7997 admin\n";
//    ofile << "gman 0000 operator\n";
//    ofile.close();
    
    std::string line;
    std::ifstream infile(filename);
    bool match = false;
    auto access_lvl = OPERATOR;
    while (std::getline(infile, line)) {
        //        std::cout << line << " <-line \n";
        std::string fname, fpass, fpost;
        fname = parser.getAttr(1, line);
        fpass = parser.getAttr(2, line);
        fpost = parser.getAttr(3, line);
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
    
    if (match) { usrptr->setName(name); usrptr->setAccessLvl(access_lvl); return usrptr; }
    return nullptr;
}
