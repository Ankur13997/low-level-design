#include "Item.h"

Item::Item(){}

Item::Item(ItemType itemType,int cost):
itemType(itemType),cost(cost)
{

}

Item::~Item()
{
}

ItemType Item::getType()
{
    return itemType;
}
int Item::getCost()
{
    return cost;
}
void  Item::setType(ItemType type){itemType=type;}
void  Item::setCost(int price){cost=price;}


