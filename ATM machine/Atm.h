#pragma once
#include "User.h"
#include<vector>
using namespace std;
class States;
class Atm
{
private:
    /* data */
    vector<shared_ptr<User>>allUsers;
    int atmAmount;
    int noOfTwoThousandNotes;
    int noOfFiveHundredNotes;
    int noOfOneHundredNotes;
    shared_ptr<States>state;
public:
    Atm(/* args */);
    ~Atm();

    vector<shared_ptr<User>> getAllUsers();
    void addUser(shared_ptr<User>user);
    int calculateAmount();
    int getAmount();
    void updateAmount(int newAmount);
    void setState(shared_ptr<States>newState)
    {
        state=newState;
    }

    shared_ptr<States> getState(){return state;}


};

