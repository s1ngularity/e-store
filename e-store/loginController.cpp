//
//  loginController.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "loginController.hpp"
#include "user.hpp"

bool LoginController::get(User &usr) { // BAD CODE ALERT!
    std::string name;
    std::cin >> name;
    if (name == "gman") { usr.setName(name); usr.setAccessLvl(OPERATOR); return true; }
    if (name != "AVasK") { return false; }
    usr.setName(name);
    usr.setAccessLvl(ADMIN);
    return true;
} // to be re-written
