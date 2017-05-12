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
    
//    TEST FEATURES: ( FOR FUTURE WORK <!> )
//    ui.alert("1) Show all items availible on the warehouse\n");
//    int ans = ui.prompt("2) Search by name\n");
//    switch(ans) {
//        case 1:
//            std::cout << "Items:\n";
//            ui.alert_items(warehouse.getItems());
//            items.push_back(warehouse[ui.prompt("Item number:\b\n") - 1]);
//            break;
//        case 2:
//            
//            break;
//        default:
//            std::cout << "Wrong way\n";
//            
//    }
    
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
    ui.alert("\n-------------CART:------------\n");
    for (auto prod : this->items) {
        std::cout << prod.getName() << " : " << prod.getPrice() << "\n";
    }
    ui.alert("\n--PRICE:--------\n");
    ui.alert(std::to_string(this->total()) + "\n");
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

void Cart::newCart() {
    UI ui;
    ui.alert("Select user name:\n");
    std::cin >> this->userName;
    setId(1); // Create new cart
    items.erase(items.begin(), items.end());
}

