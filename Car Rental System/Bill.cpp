#include "Bill.h"

Bill::Bill(shared_ptr<Reservation>reservation)
:reservation(reservation),isBillpaid(false)
{
    totalCost=Bill::computeCost();
    cout<<"Bill Genrated"<<endl;
}

Bill::~Bill()
{
}

double Bill::computeCost()
{
    return 100.0;
}