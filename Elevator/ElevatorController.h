#pragma once
#include "ElevatorCar.h"
#include <memory>
#include <queue>
using namespace std;

class ElevatorCar;

class ElevatorController
{
private:
    /* data */
    shared_ptr<ElevatorCar>elevatorCar;
    priority_queue<int, vector<int>, greater<int>> upMinPQ;   // smallest floor first
    priority_queue<int, vector<int>, less<int>> downMaxPQ;
    queue<pair<int, Direction>> pendingRequests;
public:
    ElevatorController(shared_ptr<InnerButtonDispatcher> innerButtonDispatcher);
    ~ElevatorController();
    shared_ptr<ElevatorCar> getElevator();
    bool submitInnerRequest(int floor);
    bool submitExternalRequest(int floor,Direction dir);
    void controlElevator();
};

