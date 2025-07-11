#pragma once
#include "City.h"
#include "VehicleInventoryManagement.h"
#include "Reservation.h"
#include<iostream>
#include"Vehicle.h"
#include "CarVehicle.h"
#include "ReservationStatus.h"
#include "ReservationType.h"
#include "VehicleLock.h"
#include<set>
using namespace std;

class Store
{
private:
    /* data */
    
    int storeId;
    City city;
    shared_ptr<VehicleInventoryManagement> inventory;
    set<shared_ptr<Reservation>>allReservations;
public:
    static int inline idCounter=0;
    Store();
    ~Store();
    
    void addVehicleToInventory(shared_ptr<Vehicle> vehicle);

    shared_ptr<Reservation> createReservation(shared_ptr<User> user,
    shared_ptr<Vehicle> vehicle);

    bool completeReservation(shared_ptr<Reservation>reservation);
    
    vector<shared_ptr<Vehicle>>getallVehicles();

};
