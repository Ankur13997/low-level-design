#pragma once
#include "Reservation.h"
#include<iostream>
class Bill
{
private:
    /* data */
    shared_ptr<Reservation>reservation;
    double totalCost;
    bool isBillpaid;
    
public:
    Bill(shared_ptr<Reservation>reservation);
    ~Bill();
    double computeCost();
    

};

