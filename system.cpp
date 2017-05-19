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
#include "filehandler.hpp"
#include "parser.hpp"
#include <cstdlib>

bool System::exec_flag = true;
std::string System::storeName() const { return "Store: " + name; }

User System::logIn() {
    UI interface;
    User *usr;
    while ((usr = interface.logIn()) == nullptr) {}
    interface.init_workspace(*usr);
    User usrn = User(*usr);
    delete usr;
    return usrn;
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
    int times = 1;
    if (userRights != "operator" && userRights != "admin" && times++ < 3) {
        ui.alert("<!> wrong type\nTry again: ");
        std::cin >> userRights;
        std::transform(userRights.begin(), userRights.end(), userRights.begin(), ::tolower); //converting to lower-case
    }
    User usr(name);
    if (userRights == "operator")
        usr.setAccessLvl(OPERATOR);
    if (userRights == "admin")
        usr.setAccessLvl(ADMIN);
    
    loginController.add(usr, password);
}

void System::start(User user) { // a function that keeps 'dat all up'n'runnin'
    UI ui;
    User usr;
    Warehouse warehouse;
    std::vector<Cart> store;
    Cart currentCart;
    
    
    FileHandler fh;
    Parser fParser;
    fParser.setSepChar('|');
    std::string storefile = "store.txt";
    
    warehouse.add(Product("ffxv", "games", 100.99));
    warehouse.add(Product("nier", "games", 99.99));
    warehouse.add(Product("Tali Zorah figure (ME series)", "figures", 200));
    warehouse.add(Product("Nier:automata digital edition", "c-games", 120));
    if (fh.fileExists(storefile)) {
        fh.setDestFile(storefile);
        auto lines = fh.getLines();
        if (lines.size() == 0) {
            ui.alert("<!> Store is empty. Contact the admin to fill it with products.\n");
        }
        for (auto line : lines) {
            try {
                std::string name = fParser.getAttr(1, line);
                std::string category = fParser.getAttr(2, line);
                int price = atoi(fParser.getAttr(2, line).c_str());
                Product product = Product(name, category, price);
                warehouse.add(product);
            }
            catch(ParseException exc) {
                ui.alert(exc.what());
            }
        }
    }
    else {
        fh.setDestFile(storefile);
        fh.appendToFile("");
        ui.alert("<!> Store is empty or the file is corrupted. Contact the admin to fill it with products.\n");
    }
    
    std::unique_ptr<User> usrPtr(user.identify());
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
