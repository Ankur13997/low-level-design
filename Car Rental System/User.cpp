#include "User.h"



User::User(/* args */string name,string drivingLicense):
    userId(++idCounter),name(name),drivingLicense(drivingLicense){}

int User::getId()
{
    return userId;
}
User::~User(){}