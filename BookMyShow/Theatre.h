#pragma once
#include "City.h"
#include "Screen.h"
#include "Show.h"
using namespace std;

class Theatre
{
private:
    /* data */
    int id;
    City city;
    vector<Screen>screen;
    vector<Show>show;

public:
    Theatre(/* args */int id,City city,vector<Show>show):
    id(id),city(city),show(show)
    {}
    ~Theatre(){}
    int getId()
    {
        return id;
    }
    City getCity()
    {
        return city;
    }
    vector<Screen> getScreen()
    {
        return screen;
    }
    vector<Show>& getShow()
    {
        return show;
    }

};
