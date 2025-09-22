#pragma once
#include "States.h"
class IdleState:public States
{
private:
    /* data */
public:
    IdleState(/* args */){
        cout<<"ATM is in Idle State"<<endl;
    }
    ~IdleState(){}
    void insertCard(shared_ptr<Atm> atm, shared_ptr<Card> card) override;
    void showState() override;
    
};

