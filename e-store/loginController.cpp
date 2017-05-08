//
//  loginController.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "loginController.hpp"
#include "user.hpp"
#include <fstream>

bool LoginController::get(User &usr) { // BAD CODE ALERT!
    std::string name;
    std::cin >> name;
    
    // FIND MISTAKE HERE!
    std::string fname;
    std::ifstream infile;
    std::ofstream ofile;
    ofile.open("/Sec.data");
    ofile << "Boo\n";
    ofile.close();
    infile.open("/Sec.data");
    while (infile >> fname)
    {
        std::cout << "read: " << fname << ".\n";
    }
    infile.close();
    std::cout << "NAME read from file:: " << fname << "\n";

    
    if (name == "gman") { usr.setName(name); usr.setAccessLvl(OPERATOR); return true; }
    if (name != "AVasK") { return false; }
    usr.setName(name);
    usr.setAccessLvl(ADMIN);
    return true;
} // to be re-written


