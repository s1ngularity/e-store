//
//  user.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "user.hpp"
#include "system.hpp"
#include "systemUI.hpp"
#include "loginController.hpp"

std::vector<std::string> User::command_list = {"WARNING: YOU MESSED UP WITH USER POINTER.\n" };

std::vector<std::string> Admin::command_list =
    {
        "1) Info\n",
        "2) Add user\n",
        "3) Add product\n",
        "4) Remove product\n"
        "5) Add new discount\n",
        "6) Remove discount\n",
        "7) Exit\n"
    };
std::vector<std::string> Operator::command_list =
    {
        "1) Info\n",
        "2) Add to cart\n",
        "3) Remove from cart\n",
        "4) Print cart\n",
        "5) Total cost\n",
        "6) Create new user's cart\n",
        "7) Exit\n"
    };

int User::getId() const {
    return id;
}

std::string User::getName() const {
    return name;
}

void User::setId(int t_id) { id = t_id; }
void User::setName(const std::string &t_name) { name = t_name; }

int User::getAccessLvl() const {
    return accessLvl;
}

void User::setAccessLvl(int lvl) {
    accessLvl = lvl;
}

User *User::identify() {
    if (accessLvl == ADMIN) {
        return new Admin(*this);
    }
    if (accessLvl == OPERATOR) {
        return new Operator(*this);
    }
    return nullptr;
}

std::vector<std::string> User::getCommandList() const {
    return command_list;
}

std::vector<std::string> Admin::getCommandList() const {
    return Admin::command_list;
}

std::vector<std::string> Operator::getCommandList() const {
    return Operator::command_list;
}

bool User::execute(int cmd, Cart& cart, Warehouse& warehouse) {
    UI ui;
    ui.alert("\nYOU. MESSED. UP. WITH. UsrPointer [!!!]\n");
    return false;
}

bool Admin::execute(int cmd, Cart& cart, Warehouse& warehouse) {
    UI ui;
    bool result = true;
    System system("decision core");
    switch(cmd) {
        case 1:
            ui.alert(getInfo()); //Get info
            break;
        case 2:
            system.addUser(); // Add user
            break;
        case 3:
            //Add product
            break;
        case 4:
            //Remove product
            //warehouse.remove(ui.prompt("Choose product to delete\n"));
            break;
        case 5:
            //Add new discount
            break;
        case 6:
            //Remove discount
            break;
        case 7:
            system.stopExec(); // exit
            break;
        default:
            std::cout << "No such option. Try again. \n\n";
            result = false;
            break;
    }
    
    return result;
}

bool Operator::execute(int cmd, Cart& cart, Warehouse& warehouse) {
    UI ui;
    System system("decision core");
    bool result = true;
    switch(cmd) {
        case 1:
            ui.alert(getInfo());
            break;
        case 2:
            //Add to cart
            cart.add_handler(warehouse);
            break;
        case 3:
            cart.remove_handler(warehouse); //Remove from cart
            break;
        case 4:
            cart.enlist(); //Enlist total
            break;
        case 5:
            cart.print_total();// Total cost
            break;
        case 6:
            cart.newCart();
            break;
        case 7:
            system.stopExec(); // exit
            break;
        default:
            std::cout << "No such option. Try again. \n\n";
            result = false;
            break;
    }
    
    return result;

}

