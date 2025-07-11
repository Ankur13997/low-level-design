#pragma once
#include<map>
#include<set>
#include<vector>
#include<iostream>
#include "City.h"
#include "Movie.h"
using namespace std;

class MovieController
{
private:
    /* data */
    map<City,vector<Movie>>cityVsMovies;
    vector<Movie>allMovies;
public:
    MovieController(/* args */){}
    ~MovieController(){}

    void addMovieToController(Movie movie,City city)
    {
        try
        {
            /* code */
            cityVsMovies[city].push_back(movie);
            allMovies.push_back(movie);
        }
        catch(const std::exception& e)
        {
            cout<< "Error in addMovieToController: "<<e.what() << '\n';
        }
        
        
    }
    Movie getMoiveByName(string movieName)
    {
        for (auto movie : allMovies)
        {
            if (movie.getMovieName() == movieName)
            {
                return movie;
            }
        }
        throw runtime_error("Movie not found: " + movieName);
        
       
    }
    map<City,vector<Movie>> getCityMovieController()
    {
        return cityVsMovies;
    }
    vector<Movie> getallMovies()
    {
        return allMovies;
    }
    


};

