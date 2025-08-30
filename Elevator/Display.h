#pragma once
#include "Direction.h"
class Display
{
private:
    /* data */
    Direction direction;
    int currentFloor;
public:
    Display(/* args */);
    ~Display();
    void setDirection(Direction dir);
    void setCurrentFloor(int floor);
    void showDisplay();
};


