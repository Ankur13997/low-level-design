#pragma once
#include "Show.h"
#include "Payment.h"
#include "Seat.h"
#include "City.h"
#include<vector>
#include<memory>

using namespace std;

class Booking
{
private:
    /* data */
    Show show;
    Payment payment;
    vector<shared_ptr<Seat>>bookedSeats;
    City city;
public:
    Booking(/* args */Show show,Payment payment,City city,vector<shared_ptr<Seat>>bookedSeats):
    show(show),payment(payment),city(city),bookedSeats(bookedSeats)
    {
       
        
        for (const auto& seat : this->bookedSeats) {
        cout << seat->getId() << " ";
        }
        cout << endl;
    }
    ~Booking(){}
};

