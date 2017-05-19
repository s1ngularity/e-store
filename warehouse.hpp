//
//  warehouse.hpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef warehouse_hpp
#define warehouse_hpp

#include <iostream>
#include <vector>
#include "product.hpp"

class Warehouse {
private:
    std::vector<Product> products;
    
public:
    void add(Product);
    std::vector<Product>& getItems();
    void remove(int index);
    Product get(int index) const { return products[index]; }
    Product& operator[](int index) { return products[index]; }
};

#endif /* warehouse_hpp */
