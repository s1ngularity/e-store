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

void System::loadBase(std::string storefile, Warehouse &warehouse, const User &usr) {
    UI ui;
    FileHandler fh;
    Parser fParser;
    fParser.setSepChar('|');

    if (fh.fileExists(storefile)) {
        fh.setDestFile(storefile);
        auto lines = fh.getLines();
        if (lines.size() == 0) {
            if (usr.getAccessLvl() == OPERATOR) {
                ui.alert("<!> Store is empty. Contact any admin to fill it with products.\n");
            }
            if (usr.getAccessLvl() == ADMIN) {
                ui.alert("<!> Store is empty. Add new products.\n");
            }
        }
        for (auto line : lines) {
            try {
                std::string name = fParser.getAttr(1, line);
                std::string category = fParser.getAttr(2, line);
                double price = atof(fParser.getAttr(3, line).c_str());
                int quantity = atoi(fParser.getAttr(4, line).c_str());
                ui.alert(name + category + std::to_string(price) + std::to_string(quantity));
                Product product = Product(name, category, price, quantity);
                warehouse.add(product);
            }
            catch(ParseException exc) {
                ui.alert("DEBUG:: Error occured while importing products from DB: " + exc.what());
                ui.alert("\n<!> Part of the DataBase seems to be corrupted.\nYou can leave a note in the error log.\n");
            }
        }
    }
    else {
        fh.setDestFile(storefile);
        fh.appendToFile("");
        ui.alert("<!> Store is empty or the file is corrupted. Contact the admin to fill it with products.\n");
    }
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
    
    //warehouse.add(Product("ffxv", "games", 100.99));
    //warehouse.add(Product("nier", "games", 99.99));
    //warehouse.add(Product("Tali Zorah figure (ME series)", "figures", 200));
    //warehouse.add(Product("Nier:automata digital edition", "c-games", 120));
    
    fh.setDestFile(storefile);
    fh.rewriteFile("GTA VI|games|100|2\nnier automata|games|120|3\n");
    loadBase(storefile, warehouse, usr);
    warehouse[0].decQuantity();
    ui.alert(warehouse[0].about() + "\n");
    
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
