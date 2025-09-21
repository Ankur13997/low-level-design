#pragma once
#include "../States.h"
class IdleState : public States
{
private:
    /* data */
public:
    IdleState(/* args */shared_ptr<VendingMachine>machine);
     IdleState(/* args */);
    ~IdleState();
void showState()override;
    void clickOnInsertCoinButton(shared_ptr<VendingMachine>machine) override;
};


