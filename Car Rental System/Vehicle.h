#pragma once
#include "VehicleType.h"
#include "VehicleStatus.h"
#include<string>
using namespace std;

class Vehicle
{
protected:
    
    int vechicleId;
    VehicleType type;    
    VehicleStatus status;
    string companyName;
    double hourlyRate;
    double dailyRate;
public:
    static int inline idCounter=0;
    Vehicle(VehicleType type, VehicleStatus status,string companyName,double hourlyRate,double dailyRate);
  

    int getVehicleId();
    VehicleType getVehicleType();
    VehicleStatus getVehicleStatus();
    string getCompanyName();

    double getHourlyRate();
    double getDailyRate();
    void setVehicleStatus();
    virtual double calculatePrice(int hours) =0;
    virtual ~Vehicle();

};