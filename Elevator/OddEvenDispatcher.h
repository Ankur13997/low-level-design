#pragma once
#include "ExternalButtonDispatcher.h"
#include "Direction.h"

class OddEvenDispatcher : public ExternalButtonDispatcher
{
private:
    /* data */
public:
    OddEvenDispatcher(/* args */);
    ~OddEvenDispatcher();
    void submitRequest(int floor,Direction dir);
};


