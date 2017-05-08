//
//  warehouse.cpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "warehouse.hpp"

void Warehouse::add(Product p) {
    products.push_back(p);
}

const std::vector<Product>& Warehouse::getItems() const {
    return products;
}
