//
//  systemUI.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include <iostream>
#include "systemUI.hpp"
#include "user.hpp"
#include "loginController.hpp"

int UI::prompt(std::string msg) const {
    std::cout << msg;
    int ans = -1;
    std::cout << ">>> ";
    std::cin >> ans;
    return ans;
}

void UI::alert(std::string msg) const {
    std::cout << msg;
}


void UI::alert_items(std::vector<Product> vec) {
    int i = 1;
    for (auto iter = vec.begin(); iter != vec.end(); iter++) {
        alert(std::to_string(i++) + ") " + iter->about() + "\n");
    }

}

int UI::prompt_list(std::vector<std::string> vec) {
    if (vec.empty()) {
        return -1;
    }
    if (vec.size() == 1) {
        return prompt(vec[0]);
    }
        
    for (auto iter = vec.begin(); iter != vec.end() - 1; iter++) {
        alert(*iter);
    }
    return prompt(*--vec.end());
}

void UI::init_workspace(const User& usr) {
    alert("\nWelcome, ");
    std::cout << usr.getName() << "\n";
}

bool UI::logIn (User &usr) {
    LoginController login;
    std::cout << "Log-In sequence initialized...\n";
    std::cout << "Enter your login: ";
    if (login.get(usr)) {
        std::cout << "\nLogin complete...\n";
        return true;
    }
    else {
        std::cout << "\n<!> Login procedure failure:\n no such login.\n Try again.\n\n\n\n";
        return false;
    }
}



