#pragma once
#include "../Item.h"
#include<memory>
#include<vector>
#include "../Coins.h"
using namespace std;
class VendingMachine;
class States
{
private:
    /* data */

public:
    States(/* args */);
    virtual ~States()=default;
    virtual void clickOnInsertCoinButton(shared_ptr<VendingMachine>machine){}
    virtual void clickOnStartProductSelectionButton(shared_ptr<VendingMachine>machine){}
    virtual void insertCoin(shared_ptr<VendingMachine>machine,Coin coin){}
    virtual void chooseProduct(shared_ptr<VendingMachine>machine,int codeNumber){}
    virtual int getChange(int remainingMoney){return 0;}
    virtual Item dispenseProduct(shared_ptr<VendingMachine>machine,int codeNumber){return Item();}
    virtual vector<Coin> refundFullMoney(shared_ptr<VendingMachine>machine){return {};}
    virtual void updateInventory(shared_ptr<VendingMachine>machine){};
    virtual void showState(){};

};


