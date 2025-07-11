#include "Payment.h"

Payment::Payment(shared_ptr<Bill> bill):id(++idCounter),bill(bill)
{
    cout<<"Payment Done"<<endl;
}

Payment::~Payment()
{
}
