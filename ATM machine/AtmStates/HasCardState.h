#pragma once
#include "States.h"
class HasCardState : public States
{
private:
    /* data */
public:
    HasCardState(/* args */){
        cout<<"ATM is in HasCard State"<<endl;
    }
    ~HasCardState(){}
    void authenticatePin(shared_ptr<Atm> atm, shared_ptr<Card> card,int pinCode)override;
    void  showState() override;
    
    void exit(shared_ptr<Atm> atm)override;
    
    void returnCard()override;
    
};

