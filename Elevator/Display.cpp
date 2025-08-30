#pragma once

#include "Display.h"
#include<iostream>
using namespace std;

Display::Display(){}

Display::~Display(){}
void Display::setDirection(Direction dir){Display::direction=dir;}
void Display::setCurrentFloor(int floor){Display::currentFloor=floor;}

void Display::showDisplay()
{
    cout<<"----------------------------------------------"<<endl;
    cout<<"Direction: "<<Display::direction<<endl;
    cout<<"CurrentFloor: "<<Display::currentFloor<<endl;
    cout<<"----------------------------------------------"<<endl;
}

