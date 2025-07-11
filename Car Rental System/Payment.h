#pragma once
#include "Bill.h"
#include <memory>  
#include<iostream>
using namespace std;

class Payment
{
private:
    /* data */
      int id;
    shared_ptr<Bill> bill;
  
public:
    static inline int idCounter=0;
    Payment(shared_ptr<Bill> bill);
    ~Payment();
};


