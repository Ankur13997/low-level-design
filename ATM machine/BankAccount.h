#pragma once
#include<string>
using namespace std;
class BankAccount
{
private:
    /* data */
    int balance;
    string name;
public:
    BankAccount(/* args */int balance,string name):
    balance(balance),name(name)
    {}
    ~BankAccount(){}

    int getBalance(){return balance;}
    string getName(){return name;}

    void updateAmount(int newAmount)
    {
        balance=newAmount;
    }
};
