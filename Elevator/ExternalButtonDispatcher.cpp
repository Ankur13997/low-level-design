#include "ExternalButtonDispatcher.h"
#include "ElevatorController.h"
ExternalButtonDispatcher::ExternalButtonDispatcher(/* args */)
{
    allElevator = vector<shared_ptr<ElevatorController>>();
}

ExternalButtonDispatcher::~ExternalButtonDispatcher()
{
}

void ExternalButtonDispatcher::addElevatorController(shared_ptr<ElevatorController>controller)
{
    allElevator.push_back(controller);
}

vector<shared_ptr<ElevatorController>>ExternalButtonDispatcher::getAllElevator(){return allElevator;}


