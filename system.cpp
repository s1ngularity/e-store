//
//  system.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include <memory>
#include <vector>
#include "system.hpp"
#include "systemUI.hpp"
#include "user.hpp"
#include <cstdlib>
#include "cartController.hpp"
#include "product.hpp"

bool System::exec_flag = true;
std::string System::storeName() const { return "Store: " + name; }

User System::logIn() {
    UI interface;
    User usr;
    while (not interface.logIn(usr)) {}
    interface.init_workspace(usr);
    return usr;
}

void System::start(User user) { // a function that keeps'dat'll up'n'runnin'
    UI ui;
    User usr;
    std::vector<Cart> store;
    Cart currentCart;

    std::unique_ptr<User> usrPtr(user.identify());
    std::cout << "\n" << usrPtr->getInfo();
    
    startExec();
    bool exec_result;
    while (exec_flag) {
        ui.alert("[ Current cart: " + currentCart.getUserName() + "]\n");
        if (currentCart.getUserName() == "none") { ui.alert("[! Choose cart !]\n"); }
        ui.alert("Commands: \n");
        int command = ui.prompt_list(usrPtr->getCommandList());
        //ui.alert("you chose: " + std::to_string(command) + "\n");
        //ui.alert(std::to_string(x));
        exec_result = usrPtr->execute(command, currentCart);
    }
    
    
    
}
