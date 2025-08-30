#pragma once
#include "ExpenseSplit.cpp"

class ExactSplit: public ExpenseSplit
{
private:
    /* data */
public:
    bool validate(vector<shared_ptr<Split>>& splits, double amount) override {
        
        double curr=0;
        for(auto split:splits)
        {
            curr+=split->getowedMoney();
        }
        if(curr!=amount)return false;
        return true;
    }
};

