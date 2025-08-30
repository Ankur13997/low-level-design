#include "ElevatorCar.h"
#include "ElevatorController.h"
#include "InnerButtonDispatcher.h"
#include<iostream>
using namespace std;
int main()
{
   shared_ptr<InnerButtonDispatcher> innerButtonDispatcher=make_shared<InnerButtonDispatcher>();
       shared_ptr<ElevatorController>eContoller1=make_shared<ElevatorController>(innerButtonDispatcher);
 
   innerButtonDispatcher->addElevatorController(eContoller1);

    cout<<innerButtonDispatcher->getAllElevator().size()<<endl;
    cout<<eContoller1->getElevator()->getCurrentFloor()<<endl;
    eContoller1->getElevator()->pressInnerButton(5);

    cout<<eContoller1->getElevator()->getCurrentFloor()<<endl;
    eContoller1->getElevator()->pressInnerButton(2);
    return 0;
}