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
    UI ui;
    User *usrptr;
    usrptr = new User;
    Parser parser;
    parser.setSepChar(' ');
    FileHandler fh;
    fh.setDestFile(filename);
    
    
    std::string name;
    std::string password;
    name = ui.dialogue("Enter your name: ");
    password = ui.dialogue("\npassword: ");
    
    if (!fh.fileExists(filename)) {
        ui.alert("User data not found or corrupted. Creating new.\nTemporary login: admin , pass: admin\n");
        fh.rewriteFile("admin admin admin\n");
    }
    
    bool match = false;
    auto access_lvl = OPERATOR;
    for (std::string line : fh.getLines()) {
        std::string fname, fpass, fpost;
        fname = parser.getAttr(1, line);
        fpass = parser.getAttr(2, line);
        fpost = parser.getAttr(3, line);
        std::transform(fpost.begin(), fpost.end(), fpost.begin(), ::tolower); //converting to lower-case
        
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
    
    if (match) { usrptr->setName(name); usrptr->setAccessLvl(access_lvl); return usrptr; }
    return nullptr;
}
