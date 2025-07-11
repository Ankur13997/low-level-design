#pragma once
#include<string>
#include "UserBalanceSheet.cpp"
#include<memory>

class User
{
private:
    /* data */
    int userId;
    string name;
    string phone;
    string email;
    shared_ptr<UserBalanceSheet>userSheet;
public:
    static inline int counterId=0;
    User(){}
    User(string name,string phone,string email): 
    userId(++counterId),name(name),phone(phone),email(email)
    {
        userSheet=make_shared<UserBalanceSheet>();
       
    }
    ~User(){}
    int getUserid(){return userId;}
    string getUserName(){return name;}
    shared_ptr<UserBalanceSheet>getUserSheet(){return userSheet;}

};

