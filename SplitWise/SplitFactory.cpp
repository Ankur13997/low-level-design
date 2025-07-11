#pragma once
#include "ExpenseSplit.cpp"
#include "SplitType.cpp"
#include "ExactSplit.cpp"
#include "EqualSplit.cpp"
#include "PercentageSplit.cpp"
class SplitFactory
{
private:
    /* data */
public:
    static shared_ptr<ExpenseSplit> getSplit(SplitType type)
    {
        if(type==EQUAL)
        {
            return make_shared<EqualSplit>();
        }
        else if(type==EXACT)
        {
            return make_shared<ExactSplit>();
        }
        else
        {
            return make_shared<PercentageSplit>();
        }
    } 
};

