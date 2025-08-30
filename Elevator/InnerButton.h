#pragma once

#include<memory>
using namespace std;

class InnerButtonDispatcher; 
class InnerButton
{
private:
    /* data */
    shared_ptr<InnerButtonDispatcher> dispatcher;
public:
    InnerButton(shared_ptr<InnerButtonDispatcher> innerButtonDispatcher);
    ~InnerButton();
    void pressButton(int floor,int elevatorid);
};

