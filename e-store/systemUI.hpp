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
    bool logIn(User &usr);
    void init_workspace(const User& usr);
    int prompt(std::string) const;
    void alert(std::string) const;
    int prompt_list(std::vector<std::string> vec);
};



#endif /* systemUI_hpp */
