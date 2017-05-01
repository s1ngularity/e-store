//
//  user.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "user.hpp"
#include "system.hpp"

std::vector<std::string> User::command_list = {"WARNING: YOU MESSED UP WITH USER POINTER.\n" };

std::vector<std::string> Admin::command_list =
    {
        "1) Add user\n",
        "2) Delete user\n",
        "3) Add product\n",
        "4) Edit product\n",
        "5) Remove product\n"
        "6) Add new discount\n",
        "7) Remove discount\n",
        "8) Exit\n"
    };
std::vector<std::string> Operator::command_list =
    {
        "1) Add to cart\n",
        "2) Remove from cart\n",
        "3) Print cart\n",
        "4) Print cheque\n", /*"4) Total cost\n", */
        "5) Create new user's cart\n",
        "6) Exit\n"
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

bool User::execute(int cmd, Cart& cart) {
    std::cout << "\nYOU. MESSED. UP. WITH. UsrPointer [!!!]\n";
    return false;
}

bool Admin::execute(int cmd, Cart& cart) {
    bool result = true;
    System system("decision core");
    switch(cmd) {
        case 1:
            //Add user
            break;
        case 2:
            //Delete user
            break;
        case 3:
            //Add product
            break;
        case 4:
            // Edit product
            break;
        case 5:
            //Remove product
            break;
        case 6:
            //Add new discount
            break;
        case 7:
            //Remove discount
            break;
        case 8:
            system.stopExec(); // exit
            break;
        default:
            std::cout << "No such option. Try again. \n\n";
            result = false;
            break;
    }
    
    return result;
}

bool Operator::execute(int cmd, Cart& cart) {
    System system("decision core");
    bool result = true;
    switch(cmd) {
        case 1:
            //Add to cart
            cart.add_handler();
            //ui.addToCart(); // -> ask for parameters -> system.addToCart(parameters)
            break;
        case 2:
            cart.remove_handler(); //Remove from cart
            break;
        case 3:
            cart.enlist(); //Enlist total
            break;
        case 4:
            cart.print_total();// Total cost
            break;
        case 5:
            cart.setUserName("test");
            cart.setId(1); // Create new cart
            break;
        case 6:
            system.stopExec(); // exit
            break;
        default:
            std::cout << "No such option. Try again. \n\n";
            result = false;
            break;
    }
    
    return result;

}

