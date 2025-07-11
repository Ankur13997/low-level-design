#pragma once
#include "PaymentStatus.h"
using namespace std;

class Payment
{
private:
    /* data */
    int id;
    PaymentStatus paymentStatus;
public:
    Payment(/* args */int id,PaymentStatus paymentStatus):
    id(id),paymentStatus(paymentStatus){}
    ~Payment(){}
};

