#pragma once
#include "../States.h"
class SelectionState:public States
{
private:
    /* data */
public:
    SelectionState(/* args */);
    ~SelectionState();
    
    void chooseProduct(shared_ptr<VendingMachine>machine,int codeNumber) override;
    int getChange(int remainingMoney) override;
    vector<Coin> refundFullMoney(shared_ptr<VendingMachine>machine) override;
    void showState()override;
};


