//
//  main.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include <iostream>
#include "system.hpp"
#include "systemUI.hpp"
#include "user.hpp"


int main(int argc, const char * argv[]) {
    UI ui;
    System store("e-Store 1");
    User user;
        
    ui.alert("Welcome to " + store.storeName() + "\n");
    user = store.logIn(); // this handles all logging-in processes
    store.start(user); // and this makes store operational (locked & loaded. For we are in a gun store, son).
        
    return 0;
}
