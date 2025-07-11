#pragma once
#include "TheatreController.h"
#include "MovieController.h"
#include "City.h"
#include "Show.h"
#include "Payment.h"
#include "Booking.h"
#include "Theatre.h"
#include <memory>
using namespace std;

class BookMyShow
{
private:
    unique_ptr<TheatreController>theatreContoller;
    unique_ptr<MovieController>movieController;
    //TheatreController *theatreContoller;
    //MovieController *movieController;
public:
    BookMyShow()
    {
        theatreContoller = make_unique<TheatreController>();
        movieController = make_unique< MovieController>();
    }

    ~BookMyShow()
    {
        
    }

    

    void Initialize()
    {
        createMovies();
        createTheatre();
    }

    void bookTicket(City city, string movieName, int showId, vector<int> seatIds) {
        vector<Theatre>theatres = theatreContoller->getTheaterByCity(city);
        // cout<<theatres.size()<<endl;
        for(Theatre theatre:theatres)
        {
            vector<Show>shows=theatre.getShow();
            // cout<<shows.size()<<endl;

            for(Show show: shows)
            {
                // cout<<show.getId()<<" "<<show.getMovie().getMovieName()<<endl;
                if(show.getId()==showId && show.getMovie().getMovieName()==movieName)
                {
                    // cout<<"Found"<<endl;
                    vector<shared_ptr<Seat>>availableSeat = show.getScreen().getSeat();
                    vector<shared_ptr<Seat>>seatsToBook;
                    bool isBooked=false;
                    for(auto seatId:seatIds)
                    {
                        if(!availableSeat[seatId]->getIsBooked())
                        {
                            isBooked=true;
                            availableSeat[seatId]->setIsBooked(true); 
                            seatsToBook.emplace_back(availableSeat[seatId])  ;
                            // cout<<"SeatId: "<<seatId<<" is booked successfully!"<<endl;

                        }
                        else
                        {
                            // cout<<"SeatId: "<<seatId<<" is already booked!"<<endl;
                        }
                    }

                    if(isBooked)
                    {
                    Payment payment(1, SUCCESS);  // Assume 100 per seat

                        // Step 4: Create booking
                    Booking booking(show, payment, city,seatsToBook);

                    cout << "Booking successful for Show ID: " << showId << " in city: " << city << endl;
                    }
                    else
                    {
                        cout<<"No seats are available"<<endl;
                    }
                    return;

                    // for(auto seat:availableSeat)cout<<seat.getIsBooked()<<" ";
                }
            }
            cout<<endl;

        }
        cout << "Show or movie not found in selected city!" << endl;


    }

    void createMovies()
    {
        try {
            Movie movie1(1, "Avenger", 180);
            Movie movie2(2, "IronMan", 150);
            Movie movie3(3, "Doctor Strange", 160);
            movieController->addMovieToController(movie1, Nagpur);
            movieController->addMovieToController(movie1, Delhi);
            movieController->addMovieToController(movie2, Nagpur);
            movieController->addMovieToController(movie3, Mumbai);
        } catch (const std::exception& e) {
            cerr << e.what() << '\n';
        }
    }


    void createTheatre()
    {
        try {
            Movie avenger = movieController->getMoiveByName("Avenger");
            Movie ironMan = movieController->getMoiveByName("IronMan");

              
            vector<Screen> screens1 = createScreen();
            vector<Show> shows1 = createShow({avenger, ironMan}, screens1);
            Theatre theatre1(1, Nagpur, shows1);
            theatreContoller->addTheatreToController(theatre1, Nagpur);
        
                
            vector<Screen> screens2 = createScreen();
            vector<Show> shows2 = createShow({avenger, ironMan}, screens2);
            Theatre theatre2(2, Delhi, shows2);
            theatreContoller->addTheatreToController(theatre2, Delhi);
        

        } catch (const std::exception& e) {
            cerr << e.what() << '\n';
        }
    }

    vector<Show> createShow(vector<Movie> movies, vector<Screen> screens)
    {
        try {
            Show show1(1, movies[0], screens[0], 12);
            Show show2(2, movies[1], screens[1], 8);
           
            return {show1, show2};
        } catch (const std::exception& e) {
            cerr << e.what() << '\n';
            return {};
        }
    }

    vector<Screen> createScreen()
{
    try {
        return {
            Screen(1, createSeat()),  // fresh seat copy
            Screen(2, createSeat()),
            Screen(3, createSeat())
        };
    } catch (const std::exception& e) {
        cerr << e.what() << '\n';
        return {};
    }
}


    vector<shared_ptr<Seat>> createSeat()
    {
        try {
            vector<shared_ptr<Seat>> allSeat;
            for (int i = 1; i <= 40; i++) {
                allSeat.emplace_back(make_shared<Seat>(i, SILVER, false));
            }
            for (int i = 41; i <= 70; i++) {
                allSeat.emplace_back(make_shared<Seat>(i, DIAMOND, false));
            }
            for (int i = 71; i <= 100; i++) {
                allSeat.emplace_back(make_shared<Seat>(i, PLATINUM, false));
            }
            return allSeat;
        } catch (const std::exception& e) {
            cerr << e.what() << '\n';
            return {};
        }
    }

    // void bookTicke(City city, string movieName, int showId, vector<int> seatIds) {
    //     try {
    //         // Step 1: Get the theatre list for the city
    //         vector<Theatre>& theatres = theatreContoller->getCityTheatreController()[city];
    //         cout<<theatres.size()<<endl;
    //         for (Theatre &theatre : theatres) {
    //             // cout << theatre.getId() << " ";
    //             vector<Show>& shows = theatre.getShow();
    //             cout << shows.size() << endl;;
    //             for (Show &show : shows) {
    //                 cout<< "\nChecking Show ID: " 
    //                     << show.getId()
    //                     << " Movie: " 
    //                     << show.getMovie().getMovieName()
    //                     << " Target: " 
    //                     << movieName << endl;
    //                 if (show.getId() == showId && show.getMovie().getMovieName() == movieName) {
    //                     vector<Seat>& availableSeats = show.getScreen().getSeat(); // Ensure this is a reference
    //                     vector<Seat> seatsToBook;

    //                     // Step 2: Check if selected seatIds are available
    //                     for (int seatId : seatIds) {
    //                         for (Seat &seat : availableSeats) {
    //                             if (seat.getId() == seatId && !seat.getIsBooked()) {
    //                                 seat.setIsBooked(true);  // Mark seat as booked
    //                                 seatsToBook.push_back(seat);
    //                                 break;
    //                             }
    //                         }
    //                     }

    //                     // Step 3: Create Payment (dummy)
    //                     Payment payment(1, SUCCESS);  // Assume 100 per seat

    //                     // Step 4: Create booking
    //                     Booking booking(show, payment, city, seatsToBook);

    //                     cout << "Booking successful for Show ID: " << showId << " in city: " << city << endl;
    //                     return;
    //                 }
    //             }
    //         }

    //         cout << "Show or movie not found in selected city!" << endl;
    //     } catch (const std::exception& e) {
    //         cerr << "Booking failed: " << e.what() << '\n';
    //     }
    // }
};
