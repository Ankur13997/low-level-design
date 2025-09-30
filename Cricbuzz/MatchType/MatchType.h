#pragma once
#include<string>
using namespace std;
class MatchType
{
protected:
    /* data */
    int noOfOvers;
    int maxAllowedOvers;
public:
    MatchType(/* args */){}
    virtual ~MatchType()=default;
    virtual void setOvers()=0;
    virtual string getName()=0;
    int getNoOfOvers(){return noOfOvers;}
    int getMaxAllowedOvers(){return maxAllowedOvers;}
};


