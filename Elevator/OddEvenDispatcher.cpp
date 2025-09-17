#include "OddEvenDispatcher.h"
#include "ElevatorController.h"
#include<iostream>

OddEvenDispatcher::OddEvenDispatcher(/* args */)
{
}

OddEvenDispatcher::~OddEvenDispatcher()
{
}

void OddEvenDispatcher::submitRequest(int floor, Direction dir) {
    cout << "OddEvenDispatcher: Request for floor " << floor << endl;

    shared_ptr<ElevatorController> chosenElevator = nullptr;

    // First try strict odd-even matching
    for (auto elevator : allElevator) {
        int id = elevator->getElevator()->getElevatorId();
        if ((floor % 2 == 0 && id % 2 == 0) ||
            (floor % 2 == 1 && id % 2 == 1)) {
            chosenElevator = elevator;
            break;
        }
    }

    // If no strict match found, fall back to first elevator
    if (!chosenElevator && !allElevator.empty()) {
        chosenElevator = allElevator[0];
    }

    if (chosenElevator) {
        chosenElevator->submitExternalRequest(floor, dir);
    } else {
        cout << "No elevators available!" << endl;
    }
}
