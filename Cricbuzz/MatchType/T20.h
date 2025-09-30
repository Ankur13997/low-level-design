#pragma once
#include "MatchType.h"

class T20 : public MatchType
{
private:
    /* data */
public:
    T20(/* args */){}
    ~T20(){}

    void setOvers()override
    {
        noOfOvers=5;
        maxAllowedOvers=3;
    }
    string getName()override
    {
        return "T20";
    }

};

