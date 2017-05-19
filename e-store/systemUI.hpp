//
//  systemUI.hpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef systemUI_hpp
#define systemUI_hpp

#include <iostream>
#include "user.hpp"

class UI {
public:
    void print_prompt(std::string text);
    User *logIn();
    void init_workspace(const User& usr);
    int prompt(std::string) const;
    void alert(std::string) const;
    //template <typename T>
    void alert_items(std::vector<Product> vec);
    int prompt_list(std::vector<std::string> vec);
    std::string dialogue(std::string);
    void print_cart(Cart);
    void print_total(Cart);
    void print_removeMenu(Cart);
};



#endif /* systemUI_hpp */
