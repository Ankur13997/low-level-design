#include "VehicleInventoryManagement.h"
#include<iostream>
VehicleInventoryManagement::VehicleInventoryManagement(){
    // allVehicle= unordered_map<int,shared_ptr<Vehicle>>();
    allVehicle=make_shared<unordered_map<int,shared_ptr<Vehicle>>>();
    vechicleStatus=make_shared<unordered_map<int,int>>();
}

void VehicleInventoryManagement::addVehicle(shared_ptr<Vehicle>vehicle)
{
    int id=vehicle->getVehicleId();
    
//    cout<<"vehicle id: "<<id<<endl;
     (*vechicleStatus)[id]=1;
     (*allVehicle)[id]=vehicle;
}
void VehicleInventoryManagement::update(int vechicleId,int status)
{
    if(vechicleStatus->count(vechicleId))
        (*vechicleStatus)[vechicleId]=status;
}
void VehicleInventoryManagement::_delete(int vechicleId)
{
    
    allVehicle->erase(vechicleId);
    vechicleStatus->erase(vechicleId);

}
shared_ptr<Vehicle> VehicleInventoryManagement::search(int vechicleId)
{
    if(allVehicle->count(vechicleId)>0)return (*allVehicle)[vechicleId];
    return nullptr;
}

vector<shared_ptr<Vehicle>>VehicleInventoryManagement::getallVehicles()
{
    vector<shared_ptr<Vehicle>>vehicle;
    for(auto veh=allVehicle->begin();veh!=allVehicle->end();veh++)
    {
        vehicle.push_back(veh->second);
    }
    return vehicle;
    // return {};
}
VehicleInventoryManagement::~VehicleInventoryManagement(){}