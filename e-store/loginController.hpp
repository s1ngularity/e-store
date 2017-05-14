//
//  loginController.hpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef loginController_hpp
#define loginController_hpp

#include "user.hpp"
#include "parser.hpp"


class LoginController {
public:
    bool get(User &usr); // to be re-written
    void add(const User &usr, std::string password); // adding user.
    void del(std::string name);
};

#endif /* loginController_hpp */
