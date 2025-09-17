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
    return submitExternalRequest(floor, elevatorCar->getDirection());
}

bool ElevatorController::submitExternalRequest(int floor, Direction dir) {
    int currentFloor = elevatorCar->getCurrentFloor();

    if (dir == Direction::UP) {
        if (floor >= currentFloor) {
            upMinPQ.push(floor);
        } else {
            pendingRequests.push({floor, dir});
        }
    } else {
        if (floor <= currentFloor) {
            downMaxPQ.push(floor);
        } else {
            pendingRequests.push({floor, dir});
        }
    }
    return true;
}

void ElevatorController::controlElevator() {
    while (true) {
        if (elevatorCar->getDirection() == Direction::UP) {
            if (!upMinPQ.empty()) {
                int target = upMinPQ.top();
                upMinPQ.pop();

                // move elevator step by step
                for (int f = elevatorCar->getCurrentFloor() + 1; f <= target; f++) {
                    elevatorCar->setCurrentFloor(f);
                    elevatorCar->setDisplay();
                    elevatorCar->getDisplay()->showDisplay();
                    this_thread::sleep_for(chrono::milliseconds(300));
                }
            } else {
                // no UP requests, switch to DOWN
                while (!pendingRequests.empty()) {
                    auto req = pendingRequests.front();
                    pendingRequests.pop();
                    if (req.second == Direction::DOWN) downMaxPQ.push(req.first);
                    else upMinPQ.push(req.first);
                }
                elevatorCar->setDirection(Direction::DOWN);
            }
        } else { // Direction::DOWN
            if (!downMaxPQ.empty()) {
                int target = downMaxPQ.top();
                downMaxPQ.pop();

                for (int f = elevatorCar->getCurrentFloor() - 1; f >= target; f--) {
                    elevatorCar->setCurrentFloor(f);
                    elevatorCar->setDisplay();
                    elevatorCar->getDisplay()->showDisplay();
                    this_thread::sleep_for(chrono::milliseconds(300));
                }
            } else {
                // no DOWN requests, check pending and switch UP
                while (!pendingRequests.empty()) {
                    auto req = pendingRequests.front();
                    pendingRequests.pop();
                    if (req.second == Direction::UP) upMinPQ.push(req.first);
                    else downMaxPQ.push(req.first);
                }
                elevatorCar->setDirection(Direction::UP);
            }
        }

        // idle break condition (optional)
        if (upMinPQ.empty() && downMaxPQ.empty() && pendingRequests.empty()) {
            elevatorCar->setStatus(ElevatorStatus::IDLE);
            break; // stop controller
        }
    }
}
// bool ElevatorController::submitInnerRequest(int floor) {
//     int currentFloor = elevatorCar->getCurrentFloor();
//     if (floor < 0 || floor >= 10) return false;

//     elevatorCar->setStatus(ElevatorStatus::MOVING);

//     if (currentFloor > floor) {
//         elevatorCar->setDirection(Direction::DOWN);
//         for (int flo = currentFloor - 1; flo >= floor; flo--) {
//             elevatorCar->setCurrentFloor(flo);
//             elevatorCar->setDisplay();
//             elevatorCar->getDisplay()->showDisplay();
//             std::this_thread::sleep_for(std::chrono::milliseconds(500));
//         }
//     } else if (currentFloor < floor) {
//         elevatorCar->setDirection(Direction::UP);
//         for (int flo = currentFloor + 1; flo <= floor; flo++) {
//             elevatorCar->setCurrentFloor(flo);
//             elevatorCar->setDisplay();
//             elevatorCar->getDisplay()->showDisplay();
//             std::this_thread::sleep_for(std::chrono::milliseconds(500));
//         }
//     } else {
//         // Already at floor
//         elevatorCar->getDisplay()->showDisplay();
//     }

//     elevatorCar->setStatus(ElevatorStatus::IDLE);
//     return true;
// }

// bool ElevatorController::submitExternalRequest(int floor)
// {
//     if(elevatorCar->getDirection()==Direction::UP)
//     {

//     }
//     else
//     {

//     }
//     return true;
// }



