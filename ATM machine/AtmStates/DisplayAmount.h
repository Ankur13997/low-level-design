#pragma once
#include "States.h"

class DisplayAmount:public States
{
private:
    /* data */
public:
    DisplayAmount(/* args */){
        cout<<"ATM is in DisplayAmount State"<<endl;
    }
    ~DisplayAmount(){}

    void displayBalance(shared_ptr<Atm> atm, shared_ptr<Card> card)override;

    void  showState() override;
    
    void exit(shared_ptr<Atm> atm)override;
    
    void returnCard()override;

    


};

