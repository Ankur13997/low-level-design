#include "Reservation.h"
#include "User.h"
#include "City.h"
#include<memory>



Reservation::Reservation(
    shared_ptr<User> user,
    shared_ptr<Vehicle> vehicle
    ):
    id(++Reservation::idCounter),user(user),vehicle(vehicle)
{
    pickup=City::NAGPUR;
    dropup=City::NAGPUR;
    pTime="12:00 am";
    dTime="1:00 am";
    status=ReservationStatus::SCHEDULED;
    type=ReservationType::HOURLY;
    
}

Reservation::~Reservation()
{
}

