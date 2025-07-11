#include "CarVehicle.h"

CarVehicle::CarVehicle(string companyName,double hourlyRate, double dailyRate):
        Vehicle(VehicleType::CAR,VehicleStatus::FREE,companyName,hourlyRate,dailyRate)
        {}
    
double CarVehicle::calculatePrice(int hours) {
           double price =  hours<23 ? hours*hourlyRate : dailyRate;
           return price;
    }