#pragma once

#include<vector>
#include<memory>
using namespace std;
class ElevatorController; 
class InnerButtonDispatcher
{
private:
    /* data */
    vector<shared_ptr<ElevatorController>>allElevator;
public:
    InnerButtonDispatcher(/* args */);
    ~InnerButtonDispatcher();
    void submitRequest(int floor,int elevatorId);
    void addElevatorController(shared_ptr<ElevatorController>);
    vector<shared_ptr<ElevatorController>> getAllElevator();

};

