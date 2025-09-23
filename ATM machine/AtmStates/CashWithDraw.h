#pragma once
#include "States.h"
class CashWithdrawProcessor;
class CashWithDraw :public States
{
private:
    /* data */
    shared_ptr<CashWithdrawProcessor>cashWithdrawProcessor;
public:
    CashWithDraw(/* args */);
    ~CashWithDraw(){}
    void cashWithdrawal(shared_ptr<Atm> atm, shared_ptr<Card> card,int withdrawAmount)override;

    void  showState() override;
    
    void exit(shared_ptr<Atm> atm)override;
    
    void returnCard()override;
    shared_ptr<CashWithdrawProcessor> createChain()override;
};

