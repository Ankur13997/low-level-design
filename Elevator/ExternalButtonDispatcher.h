#pragma once
#include<memory>
#include<vector>
#include "Direction.h"
using namespace std;

class ElevatorController;
class ExternalButtonDispatcher
{
protected:
    /* data */
    vector<shared_ptr<ElevatorController>>allElevator;
public:
    ExternalButtonDispatcher(/* args */);
    ~ExternalButtonDispatcher();
    virtual void submitRequest(int floor,Direction dir)=0;
    void addElevatorController(shared_ptr<ElevatorController>);
    vector<shared_ptr<ElevatorController>> getAllElevator();

};

