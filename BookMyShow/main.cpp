#include<bits/stdc++.h>
#include "BookMyShow.h"
using namespace std;

int main()
{
    BookMyShow bookmyshow;
    bookmyshow.Initialize();
    vector<int> seats = {1, 2, 3,1};
    bookmyshow.bookTicket(Nagpur, "Avenger", 1, seats);
    bookmyshow.bookTicket(Nagpur, "Avenger", 1, seats);
    bookmyshow.bookTicket(Nagpur, "Avenger", 3, seats); // Try Show ID 3 (also Avenger)

    return 0;
}
