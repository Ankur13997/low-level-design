#pragma once
#include<set>
#include<map>
#include<vector>
#include "City.h"
#include "Theatre.h"
#include<iostream>
using namespace std;

class TheatreController
{
private:
    /* data */
    map<City,vector<Theatre>>cityVsTheatre;
    vector<Theatre>allTheatre;
public:
    TheatreController(/* args */){}
    ~TheatreController(){}
    
    void addTheatreToController(Theatre theatre,City city)
    {
        try
        {
            /* code */
            cityVsTheatre[city].push_back(theatre);
            allTheatre.push_back(theatre);
        }
        catch(const std::exception& e)
        {
            cout<< "Error in addTheatreToController: "<<e.what() << '\n';
        }
        
        
    }
    vector<Theatre> getTheaterByCity(City city)
    {
        return cityVsTheatre[city];
    }
    map<City,vector<Theatre>> getCityTheatreController()
    {
        return cityVsTheatre;
    }
    vector<Theatre> getallTheatre()
    {
        return allTheatre;
    }
};

