#pragma once
#include "../States.h"
class HasMoneyState:public States
{
private:
    /* data */
public:
    HasMoneyState(/* args */);
    ~HasMoneyState();
void showState()override;
    void clickOnStartProductSelectionButton(shared_ptr<VendingMachine>machine) override;
    void insertCoin(shared_ptr<VendingMachine>machine,Coin coin)override;
    vector<Coin> refundFullMoney(shared_ptr<VendingMachine>machine)override;
};

