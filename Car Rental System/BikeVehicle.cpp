#include "BikeVehicle.h"

BikeVehicle::BikeVehicle(string companyName,double hourlyRate, double dailyRate):
    Vehicle(VehicleType::BIKE,VehicleStatus::FREE,companyName,hourlyRate,dailyRate)
    {}

double BikeVehicle::calculatePrice(int hours) {
    return hours<23 ? hours*hourlyRate : dailyRate;
}
