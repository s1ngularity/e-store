//
//  product.cpp
//  e-store
//
//  Created by Alex Vaskov on 01.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "product.hpp"

std::string Product::about() const {
    return name + " | " + category + " | " + std::to_string(price) + " < " + std::to_string(quantity) + " left in stock >";
}

bool Product::inStock() {
    if (quantity > 0) {
        return true;
    }
    return false;
}

Product::Product(std::string t_name, std::string t_category, double t_price, int t_quantity) : name(t_name), category(t_category), price(t_price), quantity(t_quantity) {
    int key1 = 0;
    for (auto x : t_name) {
        key1 += (int(x) - int('a'));
    }
    
    //std::cout << "id is: " << key1 << "\n";
    id = key1;
}

bool Product::operator==(const Product &rhs) {
    if (this->getName() == rhs.getName() && this->getPrice() == rhs.getPrice() && this->getCategory() == rhs.getCategory()) {
        return true;
    }
    return false;
}

