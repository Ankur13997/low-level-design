#include "Store.h"
#include"Vehicle.h"
#include "CarVehicle.h"
#include "ReservationStatus.h"
#include "ReservationType.h"
#include "User.h"
#include "Reservation.h"
Store::Store(){
    inventory=make_shared<VehicleInventoryManagement>();
}
Store::~Store(){}
    
void Store::addVehicleToInventory(shared_ptr<Vehicle> vehicle)
{
    inventory->addVehicle(vehicle);
    cout<<"Vehicle Added in the store!"<<endl;
}

shared_ptr<Reservation> Store::createReservation(shared_ptr<User> user,
    shared_ptr<Vehicle> vehicle)
{
    
    
    int vehicleId=vehicle->getVehicleId();

    /*
    ✅ Use lock_guard for simple cases.
    ✅ Use unique_lock when you need more control, especially with containers of mutexes, like your unordered_map<int, mutex>.
    */
    lock_guard<mutex>lock(vehiclelock[vehicleId]);

    if(vehicle->getVehicleStatus()==VehicleStatus::BOOKED)
    {
        lock_guard<mutex>coutLock(consoleMutex);
        cout<<"Vehicle is already booked"<<endl;
        return NULL;
    }

    vehicle->setVehicleStatus();
    shared_ptr<Reservation> reservation=make_shared<Reservation>(user,vehicle);
    allReservations.insert(reservation);
    lock_guard<mutex>coutLock(consoleMutex);
    cout<<"Reservation is created with: User id: "<<user->getId() <<" Vehicle Id: "<< vehicle->getVehicleId()<<endl;
    return reservation;

}

bool Store::completeReservation(shared_ptr<Reservation>reservation)
{
    allReservations.erase(reservation);
    return true;
}

vector<shared_ptr<Vehicle>>Store::getallVehicles()
{
    // return {};
    return inventory->getallVehicles();
}