#include "Atm.h"
#include "AtmStates/States.h"
#include "AtmStates/IdleState.h"
Atm::Atm(/* args */)
{
    state = make_shared<IdleState>();
    noOfTwoThousandNotes=5;
    noOfFiveHundredNotes=10;
    noOfOneHundredNotes=50;
    atmAmount=calculateAmount();
}

Atm::~Atm()
{
}

vector<shared_ptr<User>> Atm::getAllUsers(){return allUsers;}
void Atm::addUser(shared_ptr<User>user){allUsers.push_back(user);}

int Atm::calculateAmount()
{
    // return 2000*Atm::noOfTwoThousandNotes;
    return 2000*noOfTwoThousandNotes + 500*noOfFiveHundredNotes + 100*noOfOneHundredNotes;
}

int Atm::getAmount(){return atmAmount;}

void Atm::updateAmount(int newAmount)
{
    atmAmount=newAmount;
}