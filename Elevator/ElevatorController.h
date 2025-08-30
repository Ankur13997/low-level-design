#pragma once
#include "ElevatorCar.h"
#include <memory>
using namespace std;

class ElevatorCar;

class ElevatorController
{
private:
    /* data */
    shared_ptr<ElevatorCar>elevatorCar;
public:
    ElevatorController(shared_ptr<InnerButtonDispatcher> innerButtonDispatcher);
    ~ElevatorController();
    shared_ptr<ElevatorCar> getElevator();
    bool submitInnerRequest(int floor);
};

