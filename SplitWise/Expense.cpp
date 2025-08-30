#pragma once
#include "SplitType.cpp"
#include "User.cpp"
#include "Split.cpp"
#include "TimeStamp.cpp"

class Expense
{
private:
    /* data */
    int expenseId;
    shared_ptr<User> paidByUser;
    double amount;
    vector<shared_ptr<Split>>allSplits;
    SplitType type;
    string timeStamp;

public:
    static inline int counterId=0;
    Expense(shared_ptr<User> paidByUser,double amount,vector<shared_ptr<Split>>&allSplits,SplitType type):
    expenseId(++counterId),paidByUser(paidByUser),amount(amount),allSplits(allSplits),type(type)
    {
        timeStamp=TimeStamp::getCurrentTimeStamp();
    }
    ~Expense(){}

    int getExpenseId(){return expenseId;}
    shared_ptr<User>paidBy(){return paidByUser;}
    vector<shared_ptr<Split>>getAllSplits(){return allSplits;}
    double getAmount(){return amount;}
    SplitType getType(){return type;}
    string getTimeStamp(){return timeStamp;}
};


