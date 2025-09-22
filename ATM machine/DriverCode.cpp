#include<bits/stdc++.h>
#include "Atm.h"
#include "AtmStates/States.h"
#include<memory>
#include "User.h"
using namespace std;

int main()
{
    shared_ptr<Atm> atm = make_shared<Atm>();
    shared_ptr<BankAccount>account1 = make_shared<BankAccount>(1000,"ABC");
    shared_ptr<Card> card1 = make_shared<Card>("123456789",123,1234,"ABC",account1);
    shared_ptr<User> user1= make_shared<User>(card1,account1);

    auto atmState=atm->getState();
    //atmState->showState();
    atmState->insertCard(atm,card1);

    //atmState->showState();
    atmState=atm->getState();
    //atmState->showState();
    atmState->authenticatePin(atm,card1,1234);

    atmState=atm->getState();
    //atmState->showState();
    atmState->selectOperation(atm,card1,DISPLAYAMOUNT);
    
    atmState=atm->getState();
    //atmState->showState();

    atmState->displayBalance(atm,card1);

    atmState=atm->getState();
    //atmState->showState();

    atmState->selectOperation(atm,card1, CASHWITHDRAW);
    atmState=atm->getState();
    //atmState->showState();

    atmState->cashWithdrawal(atm,card1,500);
    atmState=atm->getState();
    //atmState->showState();

    atmState->selectOperation(atm,card1, CASHWITHDRAW);
    atmState=atm->getState();
    //atmState->showState();

    atmState->cashWithdrawal(atm,card1,60000);
    atmState=atm->getState();
    //atmState->showState();
    return 0;
}