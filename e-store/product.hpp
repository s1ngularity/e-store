//
//  product.hpp
//  e-store
//
//  Created by Alex Vaskov on 01.05.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef product_hpp
#define product_hpp

#include <iostream>

class Product {
private:
    std::string name = "none";
    int id = -1;
    std::string category = "noneexistent";
    double price = 0;
    
public:
    Product();
    Product(std::string t_name, std::string t_category, double t_price); // without id
    Product(std::string t_name, std::string t_category, double t_price, int t_id) : name(t_name), category(t_category), price(t_price), id(t_id) {} // constructing product with set id.
    
    int getPrice() { return price; }
    int getId() { return id; }
    std::string getName() { return name; }
    std::string getCategory() { return category; }
    
};

#endif /* product_hpp */
