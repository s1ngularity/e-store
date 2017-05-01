//
//  user.hpp
//  e-store
//
//  Created by Alex Vaskov on 21.04.17.
//  Copyright © 2017 CodeProject. All rights reserved.
//

#ifndef user_hpp
#define user_hpp

#include <iostream>
#include <vector>
#include "cartController.hpp"

enum { UNKNOWN = 0, OPERATOR, ADMIN};

class User {
private:
    std::string name;
    int id = -1;
    int accessLvl = 0;
    static std::vector<std::string> command_list;
public:
    User() : name("none"), id(-1) {}
    User(std::string t_name, int t_id) : name(t_name), id(t_id) {}
    int getId() const;
    int getAccessLvl() const;
    std::string getName() const;
    void setId(int t_id);
    void setAccessLvl(int);
    void setName(const std::string &t_name);
    User *identify();
    virtual std::string getInfo() { return "Unidentified type.\n"; }
    virtual std::vector<std::string> getCommandList() const;
    virtual bool execute(int, Cart&);
};


// -------- ADMIN: --------
class Admin : public User {
private:
    std::string instructions = "You have highest access level\n"
    "Here's what you can do: \nAdd & Edit & Delete products, prices & discounts\n";

    static std::vector<std::string> command_list;
public:
    Admin(const User &usr) {
        this->setName(usr.getName());
        setId(usr.getId());
        setAccessLvl(ADMIN);
    }
    virtual std::vector<std::string> getCommandList() const override;
    virtual std::string getInfo() override { return instructions; }
    virtual bool execute(int, Cart&) override;
};


// -------- OPERATOR: --------
class Operator : public User {
private:
    static std::vector<std::string> command_list;
    std::string instructions = "You can add & delete products in someone's cart.\nEnjoy.\n";
public:
    Operator(const User &usr) {
        this->setName(usr.getName());
        setId(usr.getId());
        setAccessLvl(OPERATOR);
    }
    virtual std::vector<std::string> getCommandList() const override;
    virtual std::string getInfo() override { return instructions; }
    virtual bool execute(int, Cart&) override;
};



#endif /* user_hpp */
