#pragma once
#include "ExpenseSplit.cpp"

class ExactSplit: public ExpenseSplit
{
private:
    /* data */
public:
    bool validate(vector<shared_ptr<Split>>& splits, double amount) override {
        
        (void)splits;
        (void)amount;
        return true;
    }
};

