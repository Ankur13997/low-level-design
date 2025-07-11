#pragma once
#include "SeatCategory.h"
class Seat
{
private:
    /* data */
    
    int seatId;
    SeatCategory seatCategory;
    bool isBooked;
    
public:
    Seat(/* args */int seatId,SeatCategory seatCategory,bool isBooked):
    seatId(seatId),seatCategory(seatCategory),isBooked(isBooked)
    {}

    ~Seat(){}
    int getId() const { return seatId; }
    bool getIsBooked() const { return isBooked; }
    void setIsBooked(bool status) { isBooked = status; }
    

};

