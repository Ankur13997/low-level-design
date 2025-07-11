#pragma once
#include"Vehicle.h"
#include "User.h"
#include "ReservationStatus.h"
#include "City.h"
#include "ReservationType.h"
#include<memory>
using namespace std;

class Reservation
{
private:
    /* data */
    int id;
    shared_ptr<User> user;
    shared_ptr<Vehicle> vehicle;
    City pickup;
    City dropup;
    string pTime;
    string dTime;
    ReservationStatus status;
    ReservationType type;
public:
    int static inline idCounter=0;
    Reservation(
    shared_ptr<User> user,
    shared_ptr<Vehicle> vehicle
   );
    ~Reservation();
};

