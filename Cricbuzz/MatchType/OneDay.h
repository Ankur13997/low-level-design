#pragma once
#include "MatchType.h"

class OneDay:public MatchType
{
private:
    /* data */
public:
    OneDay(/* args */){}
    ~OneDay(){}
    void setOvers()override
    {
        noOfOvers=50;
        maxAllowedOvers=10;
    }
    string getName()override{
        return "OneDay";
    }


};

