#pragma once
#include "Movie.h"
#include "Screen.h"
#include "Seat.h"
using namespace std;

class Show
{
private:
    /* data */
    int id;
    Movie movie;
    Screen screen;
    int startTime;
   
public:
    Show(int id,Movie movie,Screen screen,int startTime):
    id(id),movie(movie),screen(screen),startTime(startTime)
    {   // cout << "Creating Show ID: " << id << " Movie: " << movie.getMovieName() << endl;
}
    ~Show(){}
    int getId()
    {
        return id;
    }
    Movie getMovie()
    {
        return movie;
    }
    Screen& getScreen()
    {
        return screen;
    }
    int getStartTime()
    {
        return startTime;
    }
//     bool bookSeats(const vector<int>& seatIds) {
//     vector<Seat> seats = screen.getSeat(); // assuming screen has getSeats()
    
//     // Step 1: Check if all requested seats are available
//     for (int seatId : seatIds) {
//         auto it = find_if(seats.begin(), seats.end(), [&](Seat& s) { return s.getId() == seatId; });
//         if (it == seats.end() || it->getIsBooked()) {
//             cout << "Seat " << seatId << " is already booked or invalid.\n";
//             return false;
//         }
//     }

//     // Step 2: Book the seats
//     for (int seatId : seatIds) {
//         auto it = find_if(seats.begin(), seats.end(), [&](Seat& s) { return s.getId() == seatId; });
//         it->setIsBooked(true);
//     }

//     return true;
// }

};

