//
//  warehouse.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "warehouse.hpp"
#include <exception>

void Warehouse::add(Product p) {
    products.push_back(p);
}

std::vector<Product>& Warehouse::getItems() {
    return products;
}

void Warehouse::remove(int index) {
    if (products.size() == 0) {
        std::cerr << "Empty array";
        return;
    }
    products.erase(products.begin() + index - 1);
}

