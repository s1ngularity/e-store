//
//  cartController.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "cartController.hpp"
#include "systemUI.hpp"

std::string CART_NOT_CREATED_ERR = "<!> Cart not created. Create cart first.\n\n";

void Cart::add_handler() {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    //ui.alert("Usage: enter product name and id (\"name id\")\n>>>");
    //TESTING:
    Product t1("Tali Zorah figure (ME series)", "figures", 200);
    Product t2("Nier:automata digital edition", "c-games", 120);
    items.push_back(t1);
    items.push_back(t2);
    
}

void Cart::remove_handler() {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    ui.alert("Usage: enter product name and id (\"name id\")\n>>>");

}

void Cart::enlist() {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    ui.alert("\n-------------CART:------------\n");
    for (auto prod : this->items) {
        std::cout << prod.getName() << " : " << prod.getPrice() << "\n";
    }
    ui.alert("------------------------------\n");
}

void Cart::print_total() {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    ui.alert("\n--PRICE:--------\n");
    ui.alert(std::to_string(this->total()) + "\n");
    ui.alert("----------------\n");
}

double Cart::total() {
    double sum = 0;
    for (auto prod : this->items) {
        sum += prod.getPrice();
    }
    return sum;
}
