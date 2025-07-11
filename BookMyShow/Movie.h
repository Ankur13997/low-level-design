#pragma once
#include<string>
using namespace std;
class Movie
{
private:   
    int id;
    string movieName;
    int duration;

public:
    Movie(int id,string movieName, int duration):
    id(id),movieName(movieName),duration(duration){}

    ~Movie(){}
    // constexpr bool operator<(const Movie& o) const {
    //     return id < o.id;  // or name < o.name
    // }
    int getMovieId()
    {
        return id;
    }
    string getMovieName()
    {
        return movieName;
    }
    int getDuration()
    {
        return duration;
    }
};