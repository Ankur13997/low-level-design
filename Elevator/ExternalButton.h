#pragma once
#include<memory>
#include "Direction.h"
using namespace std;
// #include"ExternalButtonDispatcher.h"

class ExternalButtonDispatcher;
class ExternalButton
{
private:
    /* data */
    shared_ptr<ExternalButtonDispatcher>externalDispatcher;
public:
    ExternalButton(shared_ptr<ExternalButtonDispatcher>externalDispatcher);
    ~ExternalButton();
    void pressButton(int floor,Direction dir);
};


