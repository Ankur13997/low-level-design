#pragma once
#include "ExpenseSplit.cpp"

class EqualSplit:public ExpenseSplit
{
private:
    /* data */
public:
    bool validate(vector<shared_ptr<Split>>& splits, double amount) override {
        try
        {
            /* code */
            int userSize = splits.size();
            if (userSize == 0) return true;
            double requireMoney = 1.0*amount/userSize;
            for(auto split:splits)
            {
                if(abs(split->getowedMoney()-requireMoney)>0.01)return false;
            }
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        
        
    }
};

