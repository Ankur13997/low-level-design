#pragma once
#include "User.cpp"
#include<vector>


class Split
{
private:
    /* data */
    shared_ptr<User> user;
    double owedMoney;
public:
    Split(shared_ptr<User> user,double owedMoney):
        user(user),owedMoney(owedMoney){}
    ~Split(){}

    shared_ptr<User> getUser(){return user;}
    double getowedMoney(){return owedMoney;}
    // virtual bool validate(vector<shared_ptr<User>>involvedUser, double amount)=0;
};


