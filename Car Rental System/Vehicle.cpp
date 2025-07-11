#include "Vehicle.h"

 Vehicle::Vehicle(VehicleType type, VehicleStatus status,string companyName,double hourlyRate,double dailyRate):
    vechicleId(++idCounter),type(type),status(status),companyName(companyName),hourlyRate(hourlyRate),dailyRate(dailyRate)
    {}

int Vehicle::getVehicleId(){return vechicleId;}
VehicleType Vehicle::getVehicleType(){return type;};
VehicleStatus Vehicle::getVehicleStatus(){return status;};
string Vehicle::getCompanyName(){return companyName;}

double Vehicle::getHourlyRate(){return hourlyRate;}
double Vehicle::getDailyRate(){return dailyRate;};

void Vehicle::setVehicleStatus()
{
    status=VehicleStatus::BOOKED;
}
Vehicle::~Vehicle(){}