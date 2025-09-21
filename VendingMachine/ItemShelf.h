#pragma once
#include "Item.h"
class ItemShelf
{
private:
    /* data */
    Item item;
    int codeNumber;
    bool isSoldOut;
public:
    ItemShelf(/* args */Item item,int codeNumber, bool isSoldOut);
    ~ItemShelf();
    Item getItem();
    int getCodeNumber();
    bool getStatus();
    void setStatus();
};


