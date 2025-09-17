#include "ElevatorCar.h"
#include "ElevatorController.h"
#include "InnerButtonDispatcher.h"
#include<iostream>
#include<thread>
using namespace std;
int main()
{
    // shared_ptr<InnerButtonDispatcher> innerButtonDispatcher=make_shared<InnerButtonDispatcher>();
    // shared_ptr<ElevatorController>eContoller1=make_shared<ElevatorController>(innerButtonDispatcher);
 
    // innerButtonDispatcher->addElevatorController(eContoller1);

    // eContoller1->getElevator()->pressInnerButton(5);
    // eContoller1->getElevator()->pressInnerButton(2);
    // return 0;
    // Create dispatcher (dummy for now)
    shared_ptr<InnerButtonDispatcher> innerDispatcher = make_shared<InnerButtonDispatcher>();

    // Create 1 elevator + controller
    shared_ptr<ElevatorController> controller = make_shared<ElevatorController>(innerDispatcher);

    // Initial direction UP
    controller->getElevator()->setCurrentFloor(0);
    controller->getElevator()->setDirection(Direction::UP);
    controller->getElevator()->setStatus(ElevatorStatus::MOVING);

    cout << "=== Simulation Started ===" << endl;

    // External Requests
    controller->submitExternalRequest(3, Direction::UP);   // request at floor 3 going UP
    controller->submitExternalRequest(7, Direction::UP);   // request at floor 7 going UP
    controller->submitExternalRequest(2, Direction::DOWN); // request at floor 2 going DOWN (will go in pending)

    // Internal Requests
    controller->submitInnerRequest(9); // passenger inside requests floor 9
    controller->submitInnerRequest(1); // passenger inside requests floor 1 (pending DOWN)

    // Run controller in a separate thread (simulate real elevator loop)
    thread t([&]() {
        controller->controlElevator();
    });

    t.join();

    cout << "=== Simulation Finished ===" << endl;
    return 0;
}