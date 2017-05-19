//
//  cartController.hpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef cartController_hpp
#define cartController_hpp

#include <iostream>
#include <vector>
#include "product.hpp"
#include "warehouse.hpp"


class Cart {
private:
    std::string userName = "none";
    int id = -1;
    std::vector<Product> items;
    //std::vector<Product>
public:
    std::string getUserName() { return userName; }
    int getId() { return id; }
    void setId(int t_id) { id = t_id; }
    void setUserName(std::string t_userName) { userName = t_userName; }
    void add_handler(Warehouse &);
    //void add(Product);
    void remove_handler(Warehouse &);
    //void remove(Product);
    void enlist();
    void print_total();
    double total();
    std::vector<Product> getItems();
    void remove(int index);
    void newCart();
};
#endif /* cartController_hpp */
