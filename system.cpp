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


void System::removeProd(Warehouse &warehouse) {
    UI ui;
    
    ui.alert("Items:\n");
    ui.alert_items(warehouse.getItems());
    int e_id = ui.prompt("Product to delete:\b\n");
    if ((e_id > 0) && (e_id <= warehouse.getItems().size())) {
            warehouse.remove(e_id - 2);
    }
    else {
        ui.alert("<!> Wrong product number - no such product\n");
    }
}

void System::addProd(Warehouse &warehouse) {
    UI ui;
    std::string name = ui.dialogue("To ADD new product, enter the name: ");
    std::string category = ui.dialogue("category: ");
    int price = atof(ui.dialogue("price").c_str());
    int quantity = atoi(ui.dialogue("and quantity: ").c_str());
    
    Product new_prod(name, category, price, quantity);
    warehouse.add(new_prod);
}



void System::saveBase(std::string storefile, Warehouse &warehouse) {
    char SepChar = '|';
    UI ui;
    FileHandler fh;
    Parser fParser;
    fParser.setSepChar(SepChar);
    
    if (warehouse.getItems().size() == 0) {
        ui.alert("<!> It seems that the warehouse is empty...\n");
        return;
    }
    
    fh.setDestFile(storefile);
    fh.rewriteFile(warehouse[0].getName() + SepChar + warehouse[0].getCategory() + SepChar + std::to_string(warehouse[0].getPrice()) + SepChar + std::to_string(warehouse[0].getQuantity()) + "\n");
    
    for (int i = 1; i < warehouse.getItems().size(); i++) {
        fh.rewriteFile(warehouse[i].getName() + SepChar + warehouse[i].getCategory() + SepChar + std::to_string(warehouse[i].getPrice()) + SepChar + std::to_string(warehouse[i].getQuantity()) + "\n");
    }
    ui.alert("DB sync...\nDone.\n");
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
                ui.alert("<::>" + name + category + std::to_string(price) + std::to_string(quantity)); // DELETE <!>
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
    //fh.rewriteFile("GTA VI|games|100|2\nnier automata|games|120|3\n");
    
    loadBase(storefile, warehouse, usr);
    
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
    for (auto item : warehouse.getItems()) {
        ui.alert(item.getName() + " : " + std::to_string(item.getQuantity()) + "\n");
    }
    saveBase(storefile, warehouse);
    
}
