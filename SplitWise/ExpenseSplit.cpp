#pragma once
#include "Split.cpp"
#include<iostream>
class ExpenseSplit
{
private:
    /* data */
public:
    ExpenseSplit(/* args */){}
    ~ExpenseSplit(){}

    virtual bool validate(vector<shared_ptr<Split>>&splits, double amount)=0;

};

