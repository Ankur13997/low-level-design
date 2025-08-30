#include "InnerButtonDispatcher.h"
#include "ElevatorController.h" 
#include<vector>
#include<memory>
#include<iostream>
using namespace std;

InnerButtonDispatcher::InnerButtonDispatcher(/* args */){
    allElevator=vector<shared_ptr<ElevatorController>>();
}
InnerButtonDispatcher::~InnerButtonDispatcher(){}

void InnerButtonDispatcher::submitRequest(int floor,int elevatorId)
{
    cout<<"InnerButtonDispatcher: "<<elevatorId<<endl;
    cout<<allElevator.size()<<endl;
    for(auto elevator:allElevator)
    {
        if(elevator->getElevator()->getElevatorId()==elevatorId)
        {
            elevator->submitInnerRequest(floor);
        }
    }
}

void InnerButtonDispatcher::addElevatorController(shared_ptr<ElevatorController>controller)
{
    allElevator.push_back(controller);
}

vector<shared_ptr<ElevatorController>>InnerButtonDispatcher::getAllElevator(){return allElevator;}

