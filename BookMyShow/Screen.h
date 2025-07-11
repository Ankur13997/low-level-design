#pragma once
#include "Seat.h"
#include<vector>
using namespace std;

class Screen
{
private:
    /* data */
    int id;
    vector<shared_ptr<Seat>>seats;
public:
    Screen(/* args */int id,vector<shared_ptr<Seat>>seats):
    id(id),seats(seats)
    {}
    ~Screen(){}

    vector<shared_ptr<Seat>> getSeat()
    {
        return seats;
    }
};
