#pragma once

#include "Display.h"
#include "Direction.h"
#include "ElevatorStatus.h"
#include "InnerButton.h"
#include <memory>

using namespace std;

class InnerButton;
class ElevatorCar {
private:
    int id;
    ElevatorStatus status;
    shared_ptr<Display> display;
    Direction direction;
    int currentFloor;
    shared_ptr<InnerButton> innerButton;


public:
    ElevatorCar(shared_ptr<InnerButtonDispatcher> innerButtonDispatcher);
    ~ElevatorCar();

    int getElevatorId();
    int getCurrentFloor();
    Direction getDirection();
    ElevatorStatus getStatus();
    shared_ptr<Display> getDisplay();
    shared_ptr<InnerButton> getInnerButton();

    void setCurrentFloor(int currentFloor);
    void setDirection(Direction direction);
    void setStatus(ElevatorStatus status);
    void setDisplay();

    void pressInnerButton(int floor);  
};
