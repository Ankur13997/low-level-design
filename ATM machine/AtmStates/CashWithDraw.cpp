#include "CashWithDraw.h"
#include "../Atm.h"
#include "../Card.h"
#include "States.h"
#include "IdleState.h"
#include "SelectionState.h"
#include "../CashWithdrawProcessor/CashWithdrawProcessor.h"

CashWithDraw::CashWithDraw(/* args */){
        cout<<"ATM is in CashWithDraw State"<<endl;
        cashWithdrawProcessor= createChain();
}


shared_ptr<CashWithdrawProcessor> CashWithDraw::createChain()
{
    shared_ptr<CashWithdrawProcessor> twoThousandsProcessors = make_shared<twoThousandsProcessor>();
    shared_ptr<CashWithdrawProcessor> fiveHundredProcessors = make_shared<fiveHundredProcessor>();
    shared_ptr<CashWithdrawProcessor> oneHundredProcessors = make_shared<oneHundredProcessor>();

    twoThousandsProcessors->setNextProcessor(fiveHundredProcessors);
    fiveHundredProcessors->setNextProcessor(oneHundredProcessors);

    return twoThousandsProcessors;
}


void CashWithDraw::cashWithdrawal(shared_ptr<Atm> atm, shared_ptr<Card> card,int withdrawAmount)
{
    int atmBalance= atm->getAmount();
    int accountBalnce = card->getBankAccount()->getBalance();
    if(atmBalance < withdrawAmount )
    {
        cout<<"Insufficient Balance in the ATM"<<endl;
        exit(atm);
        return ;
    }

    if(accountBalnce < withdrawAmount)
    {
        cout<<"Insufficient Balance in your account"<<endl;
        exit(atm);
        return ;
    }
    vector<int>deductions={0,0,0}; // 2000,500,100
    cashWithdrawProcessor->deductMoney(atm,withdrawAmount,deductions);

    if(deductions.empty())
    {
        cout<<"Insufficient Notes available in the ATM"<<endl;
    }
    else
    {
        atm->updateAmount(atmBalance - withdrawAmount );
        card->getBankAccount()->updateAmount(accountBalnce - withdrawAmount);
        atm->updatetwo(deductions[0]);
        atm->updatefive(deductions[1]);
        atm->updateone(deductions[2]);
        cout<<"Please Collect your cash"<<endl;
        cout<<"Your remaining amount: "<<accountBalnce - withdrawAmount<<endl;

    }
   
    atm->setState(make_shared<SelectionState>());

}
void  CashWithDraw::showState() 
{
    cout<<"CashWithDraw State"<<endl;
}
void CashWithDraw::returnCard() 
{
    cout<<"Please collect your card"<<endl;
}
void CashWithDraw::exit(shared_ptr<Atm> atm) 
{
    returnCard();
    atm->setState(make_shared<IdleState>());
    cout<<"Exit happens"<<endl;
}