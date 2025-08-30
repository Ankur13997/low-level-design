#include "InnerButton.h"
#include "InnerButtonDispatcher.h"  
#include<memory>
#include<iostream>
using namespace std;
InnerButton::InnerButton(shared_ptr<InnerButtonDispatcher> innerButtonDispatcher){
    dispatcher = innerButtonDispatcher;
}
InnerButton::~InnerButton(){}

void InnerButton::pressButton(int floor,int elevatorid)
{
    cout<<"Inner Button request: "<<floor<<endl;
    dispatcher->submitRequest(floor,elevatorid);
}



