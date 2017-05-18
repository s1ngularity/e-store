//
//  cartController.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "cartController.hpp"
#include "systemUI.hpp"
#include "warehouse.hpp"

std::string CART_NOT_CREATED_ERR = "<!> Cart not created. Create cart first.\n\n";


std::vector<Product> Cart::getItems() {
    return this->items;
}

void Cart::remove(int index) {
    this->items.erase(this->items.begin() + index - 1);
}


void Cart::add_handler(const Warehouse& warehouse) {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    
    
    std::cout << "Items:\n";
    ui.alert_items(warehouse.getItems());
    int e_id = ui.prompt("Item number:\b\n");
    if ((e_id > 0) && (e_id <= warehouse.getItems().size())) {
        items.push_back(warehouse[e_id - 1]);
    }
    else {
        ui.alert("<!> Wrong product number - no such product\n");
    }
    
}

void Cart::remove_handler() {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    if (this->items.size() == 0) {
        ui.alert("Cart is already empty!\n");
        return;
    }
    
    ui.alert("\nItems in the cart:\n");
    ui.alert_items(this->getItems());
    int e_id = ui.prompt("Choose product number to delete:\n");
    if ((e_id > 0) && (e_id <= items.size())) {
        remove(e_id);
    }
    else {
        ui.alert("<!> Wrong product number - no such product\n");
    }

}

void Cart::enlist() {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    ui.print_cart(*this);
}

void Cart::print_total() {
    UI ui;
    if (this->getId() == -1) {
        ui.alert(CART_NOT_CREATED_ERR);
        return;
    }
    ui.print_total(*this);
}

double Cart::total() {
    double sum = 0;
    for (auto prod : this->items) {
        sum += prod.getPrice();
    }
    return sum;
}

void Cart::newCart() {
    UI ui;
    ui.alert("Select user name:\n");
    std::cin >> this->userName;
    setId(1); // Create new cart
    items.erase(items.begin(), items.end());
}

