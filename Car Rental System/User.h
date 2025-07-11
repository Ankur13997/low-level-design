#pragma once
#include<string>
using namespace std;

class User
{
private:
    /* data */
    
    int userId;
    string name;
    string drivingLicense;

public:
    static inline int idCounter=0;   
    User(/* args */string name,string drivingLicense);
    int getId();
    ~User();
};

