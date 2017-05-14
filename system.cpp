//
//  system.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include "system.hpp"
#include "systemUI.hpp"
#include "user.hpp"
#include <cstdlib>
#include "cartController.hpp"
#include "product.hpp"
#include "warehouse.hpp"
#include "loginController.hpp"

bool System::exec_flag = true;
std::string System::storeName() const { return "Store: " + name; }

User System::logIn() {
    UI interface;
    User usr;
    while (not interface.logIn(usr)) {}
    interface.init_workspace(usr);
    return usr;
}

void System::addUser() {
    UI ui;
    LoginController loginController;
    ui.alert("To add new user: \nEnter name: ");
    std::string name;
    std::cin >> name;
    ui.alert("password: ");
    std::string password;
    std::cin >> password;
    ui.alert("choose rights: operator / admin :");
    std::string userRights;
    std::cin >> userRights;
    std::transform(userRights.begin(), userRights.end(), userRights.begin(), ::tolower); //converting to lower-case
    if (userRights != "operator" && userRights != "admin") {
        ui.alert("<!> wrong type\nTry again: ");
        std::cin >> userRights;
        std::transform(userRights.begin(), userRights.end(), userRights.begin(), ::tolower); //converting to lower-case
        return;
    }
    User usr(name);
    if (userRights == "operator")
        usr.setAccessLvl(OPERATOR);
    if (userRights == "admin")
        usr.setAccessLvl(ADMIN);
    
    loginController.add(usr, password);
}

void System::start(User user) { // a function that keeps'dat'll up'n'runnin'
    UI ui;
    User usr;
    Warehouse warehouse;
    std::vector<Cart> store;
    Cart currentCart;
    
    warehouse.add(Product("ffxv", "games", 100.99));
    warehouse.add(Product("nier", "games", 99.99));
    warehouse.add(Product("Tali Zorah figure (ME series)", "figures", 200));
    warehouse.add(Product("Nier:automata digital edition", "c-games", 120));
    
    
    std::unique_ptr<User> usrPtr(user.identify());
    std::cout << "\n" << usrPtr->getInfo();
    
    startExec();
    bool exec_result;
    while (exec_flag) {
        if (user.getAccessLvl() == OPERATOR) {
            ui.alert("[ Current cart: " + currentCart.getUserName() + " ]\n");
            if (currentCart.getUserName() == "none") { ui.alert("<!> Choose cart \n\n"); }
        }
        
        ui.alert("Commands: \n");
        int command = ui.prompt_list(usrPtr->getCommandList());
        //ui.alert("you chose: " + std::to_string(command) + "\n");
        //ui.alert(std::to_string(x));
        exec_result = usrPtr->execute(command, currentCart, warehouse);
    }
    
    
    
}
