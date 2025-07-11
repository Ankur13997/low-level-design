#pragma once
#include "Vehicle.h"
using namespace std;

class BikeVehicle:public Vehicle
{
private:
    /* data */
public:
    BikeVehicle(string companyName,double hourlyRate, double dailyRate);

    double calculatePrice(int hours)  override;

};

