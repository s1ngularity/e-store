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
    int quantity = 0;
    
public:
    Product();
    Product(std::string t_name, std::string t_category, double t_price, int t_quantity); // without id
    Product(std::string t_name, std::string t_category, double t_price, int t_quantity, int t_id) : name(t_name), category(t_category), price(t_price), quantity(t_quantity), id(t_id) {} // constructing product with set id.
    
    int getPrice() const { return price; }
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    std::string about() const;
    void decQuantity() { if (quantity > 0) { --quantity; } };
    void incQuantity() { ++quantity; };
    Product operator--(int x) { this->decQuantity(); return *this; }
    Product operator++(int x) { this->incQuantity(); return *this; }
    bool inStock();
    bool operator==(const Product &rhs);
};

#endif /* product_hpp */
