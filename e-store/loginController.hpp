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


class LoginController {
public:
    bool get(User &usr); // to be re-written
    bool add(const User &usr); // adding user.
};

#endif /* loginController_hpp */
