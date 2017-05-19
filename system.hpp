//
//  system.hpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef system_hpp
#define system_hpp

#include <iostream>
#include "user.hpp"

class System {
private:
    std::string name;
    static bool exec_flag; // menu loop execution
public:
    System(std::string t_name): name(t_name) {}
    std::string storeName() const;
    User logIn();
    void start(User);
    void startExec() { exec_flag = true; }
    void stopExec() { exec_flag = false; }
    void addUser();
    void loadBase(std::string, Warehouse &, const User &);
};

#endif /* system_hpp */
