#include "Inventory.h"


Inventory::Inventory(/* args */)
{
   
}

Inventory::~Inventory()
{
}

void Inventory::addItem(shared_ptr<ItemShelf>item)
{
    items.push_back(item);
}
shared_ptr<ItemShelf> Inventory::getItemByCode(int codeNumber)
{
    for(auto item:items)
    {
        if(item->getCodeNumber()==codeNumber && item->getStatus()==false)
        {
            return item;
        }
    }
    return nullptr;
}
vector<shared_ptr<ItemShelf>>& Inventory::getItems(){return items;}