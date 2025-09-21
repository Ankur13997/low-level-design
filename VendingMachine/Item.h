#pragma once
#include "ItemType.h"

class Item
{
private:
    ItemType itemType;
    int cost;

public:
    Item();
    Item(ItemType itemType,int cost);
    ~Item();

    ItemType getType();
    int getCost();
    void setType(ItemType type);
    void setCost(int price);
    
};
