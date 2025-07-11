#pragma once
#include "Vehicle.h"
using namespace std;

class CarVehicle:public Vehicle
{
public:
    CarVehicle(string companyName,double hourlyRate, double dailyRate);
    double calculatePrice(int hours)  override;
};
