#pragma once
#include "Vehicle.h"
#include<memory>
#include<vector>
#include<unordered_map>
using namespace std;

class VehicleInventoryManagement
{
private:
    /* data */
    shared_ptr<unordered_map<int,shared_ptr<Vehicle>>>allVehicle;
    shared_ptr<unordered_map<int,int>>vechicleStatus;
public:
    VehicleInventoryManagement();

    void addVehicle(shared_ptr<Vehicle>vehicle);
    void update(int vechicleId,int status);
    void _delete(int vechicleId);
    shared_ptr<Vehicle> search(int vechicleId);
    vector<shared_ptr<Vehicle>>getallVehicles();
    virtual ~VehicleInventoryManagement();
};

