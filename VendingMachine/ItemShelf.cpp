#include "ItemShelf.h"

ItemShelf::ItemShelf(/* args */Item item,int codeNumber, bool isSoldOut):
item(item),codeNumber(codeNumber),isSoldOut(isSoldOut)
{
}

ItemShelf::~ItemShelf()
{
}

Item ItemShelf::getItem(){return item;}
int ItemShelf::getCodeNumber(){return codeNumber;}
bool ItemShelf::getStatus(){return isSoldOut;}
void ItemShelf::setStatus(){isSoldOut=true;}