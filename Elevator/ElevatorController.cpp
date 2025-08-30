#include "ElevatorController.h"
#include <thread>
#include <memory>
using namespace std;

ElevatorController::ElevatorController(shared_ptr<InnerButtonDispatcher> innerButtonDispatcher){
     elevatorCar=make_shared<ElevatorCar>(innerButtonDispatcher);
}
ElevatorController::~ElevatorController(){}

shared_ptr<ElevatorCar> ElevatorController::getElevator(){return elevatorCar;}

bool ElevatorController::submitInnerRequest(int floor) {
    int currentFloor = elevatorCar->getCurrentFloor();
    if (floor < 0 || floor >= 10) return false;

    elevatorCar->setStatus(ElevatorStatus::MOVING);

    if (currentFloor > floor) {
        elevatorCar->setDirection(Direction::DOWN);
        for (int flo = currentFloor - 1; flo >= floor; flo--) {
            elevatorCar->setCurrentFloor(flo);
            elevatorCar->setDisplay();
            elevatorCar->getDisplay()->showDisplay();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    } else if (currentFloor < floor) {
        elevatorCar->setDirection(Direction::UP);
        for (int flo = currentFloor + 1; flo <= floor; flo++) {
            elevatorCar->setCurrentFloor(flo);
            elevatorCar->setDisplay();
            elevatorCar->getDisplay()->showDisplay();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    } else {
        // Already at floor
        elevatorCar->getDisplay()->showDisplay();
    }

    elevatorCar->setStatus(ElevatorStatus::IDLE);
    return true;
}



