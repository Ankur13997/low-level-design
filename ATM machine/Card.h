#pragma once
#include "BankAccount.h"
#include<memory>
class Card
{
private:
    /* data */
    string cardNumber;
    int cvv;
    int pinCode;
    string Name;
    shared_ptr<BankAccount>bankAccount;

public:
    Card(string cardNumber,int cvv,int pinCode,string Name,shared_ptr<BankAccount>bankAccount):
    cardNumber(cardNumber),cvv(cvv),pinCode(pinCode),Name(Name),bankAccount(bankAccount)
    {}
    ~Card()
    {}

    int getPinCode(){return pinCode;}

    shared_ptr<BankAccount> getBankAccount(){return bankAccount;}
    bool validate(int pin)
    {
        return pinCode==pin;
    }
};


