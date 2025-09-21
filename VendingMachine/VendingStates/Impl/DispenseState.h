#pragma once
#include "../States.h"

class DispenseState:public States
{
private:
    /* data */
public:
    DispenseState(/* args */shared_ptr<VendingMachine>machine,int codeNumber);
    ~DispenseState();
    void showState()override;
    Item dispenseProduct(shared_ptr<VendingMachine>machine,int codeNumber) override;
    //void updateInventory(shared_ptr<VendingMachine>machine) override;
};

