#pragma once
#include<unordered_map>
#include "Balance.cpp"
#include<memory>
using namespace std;

class UserBalanceSheet
{
private:
    unordered_map<int,Balance>userSheet;
    double totalExpense;
    double totalPayment;
    double totalOwed;
    double totalRecieveBack;
public:
    UserBalanceSheet(){
        userSheet=unordered_map<int,Balance>();
        totalExpense=0;
        totalPayment=0;
        totalOwed=0;
        totalRecieveBack=0;
    }
    ~UserBalanceSheet(){}

    void setOwed(int userId,double owed)
    {
        userSheet[userId].owed+=owed;
        totalOwed+=owed;
    }
    void setRecieve(int userId,double recieve)
    {
        userSheet[userId].recieve+=recieve;
        totalRecieveBack+=recieve;
    }
    void setTotalExpense(double amount)
    {
        totalExpense+=amount;
    }
    double getTotalExpense(){return totalExpense;}
    double getowed(){return totalOwed;}
    double getRecieve(){return totalRecieveBack;}
    unordered_map<int,Balance>getUserSheet(){return userSheet;}

};
