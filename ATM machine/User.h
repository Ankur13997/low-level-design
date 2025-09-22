#pragma once
#include "Card.h"
class User
{
private:
    /* data */
    shared_ptr<Card>card;
    shared_ptr<BankAccount>bankAccount;
public:
    User(shared_ptr<Card>card,shared_ptr<BankAccount>bankAccount):
    card(card),bankAccount(bankAccount)
    {

    }
    ~User(){}
};

