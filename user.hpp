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
    User(std::string t_name) : name(t_name), id(1) {}
    User(std::string t_name, int t_id) : name(t_name), id(t_id) {}
    virtual ~User() {}
    int getId() const;
    int getAccessLvl() const;
    std::string getName() const;
    void setId(int t_id);
    void setAccessLvl(int);
    void setName(const std::string &t_name);
    User *identify();
    virtual std::string getInfo() { return "Unidentified type.\n"; }
    virtual std::vector<std::string> getCommandList() const;
    virtual bool execute(int, Cart&, Warehouse&);
};


// -------- ADMIN: --------
class Admin : public User {
private:
    std::string instructions = "--- e-Store system prototype: --------------------\n\n"
      "Welcome to Admin's Control Panel beta\nYou have the highest access level\n"
      "Here's what you can do: \nAdd & Delete products, Add users,\n Add & Delete discounts\n"
      "---------------------------------------------------\n\n";

    static std::vector<std::string> command_list;
public:
    Admin(const User &usr) {
        this->setName(usr.getName());
        setId(usr.getId());
        setAccessLvl(ADMIN);
    }
    virtual std::vector<std::string> getCommandList() const override;
    virtual std::string getInfo() override { return instructions; }
    virtual bool execute(int, Cart&, Warehouse&) override;
};


// -------- OPERATOR: --------
class Operator : public User {
private:
    static std::vector<std::string> command_list;
    std::string instructions = "--- e-Store system prototype: --------------------\n\n"
      "Welocme to Operator's Control Panel beta\n"
      "You can add & delete products in someone's cart,\nGet total and print products in cart\n"
      "Good luck.\n"
      "---------------------------------------------------\n\n";
public:
    Operator(const User &usr) {
        this->setName(usr.getName());
        setId(usr.getId());
        setAccessLvl(OPERATOR);
    }
    virtual std::vector<std::string> getCommandList() const override;
    virtual std::string getInfo() override { return instructions; }
    virtual bool execute(int, Cart&, Warehouse&) override;
};



#endif /* user_hpp */
