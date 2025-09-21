#pragma once
#include "ItemShelf.h"
#include<memory>
#include<vector>
using namespace std;
class Inventory
{
private:
    /* data */
    vector<shared_ptr<ItemShelf>>items;
public:
    Inventory(/* args */);
    ~Inventory();
    void addItem(shared_ptr<ItemShelf>item);
    shared_ptr<ItemShelf> getItemByCode(int codeNumber);
    vector<shared_ptr<ItemShelf>>& getItems();
};

