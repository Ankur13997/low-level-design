#pragma once
#include<string>

class Person
{
private:
    /* data */
    std::string name;
    int age;
public:
    Person(std::string name,int age):
    name(name),age(age)
    {}
    ~Person(){}
    std::string getPlayerName(){return name;}
};

