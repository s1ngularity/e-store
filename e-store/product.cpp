//
//  product.cpp
//  e-store
//
//  Created by Alex Vaskov on 01.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#include "product.hpp"

Product::Product(std::string t_name, std::string t_category, double t_price) : name(t_name), category(t_category), price(t_price) {
    int key1 = 0;
    for (auto x : t_name) {
        key1 += (int(x) - int('a'));
    }
    
    //std::cout << "id is: " << key1 << "\n";
    id = key1;
}

