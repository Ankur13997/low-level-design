#pragma once
#include<memory>
#include<iostream>
#include "../TransactionType.h"
using namespace std;
class Atm;
class Card;
class States
{
private:
    /* data */
public:
    States(/* args */);
    virtual ~States()=default;
    virtual void insertCard(shared_ptr<Atm> atm, shared_ptr<Card> card)
    {
        cout<<"OOPS!! Something went wrong"<<endl;
    }
    virtual void authenticatePin(shared_ptr<Atm> atm, shared_ptr<Card> card,int pinCode)
    {
        cout<<"OOPS!! Something went wrong"<<endl;
    }
    virtual void selectOperation(shared_ptr<Atm> atm, shared_ptr<Card> card,TransactionType txnType)
    {
        cout<<"OOPS!! Something went wrong"<<endl;
    }
    virtual void cashWithdrawal(shared_ptr<Atm> atm, shared_ptr<Card> card,int withdrawAmount)
    {
        cout<<"OOPS!! Something went wrong"<<endl;
    }
    virtual void displayBalance(shared_ptr<Atm> atm, shared_ptr<Card> card)
    {
        cout<<"OOPS!! Something went wrong"<<endl;
    }
    virtual void returnCard()
    {
        cout<<"OOPS!! Something went wrong"<<endl;
    }
    virtual void exit(shared_ptr<Atm> atm)
    {
        cout<<"OOPS!! Something went wrong"<<endl;
    }
    virtual void showState(){
        cout<<"OOPS!! Something went wrong"<<endl;
    }
};


