#include<iostream>
#include "VendingMachine.h"
#include "VendingStates/States.h"
using namespace std;

void fillUpInventory(shared_ptr<VendingMachine>machine)
{
    vector<std::shared_ptr<ItemShelf>> & itemShelfs = machine->getInventory()->getItems();

    for(int i=0;i<10;i++)
    {
       Item item;
        if(i<3)
        {
            item.setType(COKE);
            item.setCost(20);
            itemShelfs.emplace_back(make_shared<ItemShelf>(item,101+i,false));
        }
        else if(i<6)
        {
            
            item.setType(SODA);
            item.setCost(15);
            itemShelfs.emplace_back(make_shared<ItemShelf>(item,101+i,false));

        }
        else
        {
            item.setType(ItemType::PEPSI);
            item.setCost(25);
            itemShelfs.emplace_back(make_shared<ItemShelf>(item,101+i,false));

        }
    }
}

void DisplayInventory(shared_ptr<VendingMachine>machine)
{
     vector<std::shared_ptr<ItemShelf>> &itemShelfs = machine->getInventory()->getItems();

    cout << "Vending Machine Inventory:\n";
    for (auto &shelf : itemShelfs)
    {
        Item item = shelf->getItem();  // Assuming ItemShelf has getItem() method
      
        cout    << "Type: ";

        // Print item type as string
        switch (item.getType())  // Assuming Item has getType()
        {
        case COKE:
            cout << "COKE";
            break;
        case SODA:
            cout << "SODA";
            break;
        case PEPSI:
            cout << "PEPSI";
            break;
        default:
            cout << "UNKNOWN";
        }

        cout << ", Cost: " << item.getCost()
             << ", Occupied: " << (shelf->getStatus() ? "Yes" : "No") << "\n";
    }

}
void Initialize(shared_ptr<VendingMachine>machine)
{
    fillUpInventory(machine);
    DisplayInventory(machine);
}



int main()
{
    shared_ptr<VendingMachine> machine=make_shared<VendingMachine>();
    Initialize(machine);
      
    cout<<"|"<<endl;
    cout<<"clicking on InsertCoinButton"<<endl;
    cout<<"|"<<endl;

    shared_ptr<States> vendingState = machine->getState();
    // vendingState->showState();
    vendingState->clickOnInsertCoinButton(machine);
// vendingState->showState();
    //hasMoneyState
    vendingState = machine->getState();
    vendingState->insertCoin(machine,Coin::TEN);
    vendingState->insertCoin(machine,Coin::TWENTY);
    vendingState->clickOnStartProductSelectionButton(machine);
// vendingState->showState();
    //SelectionState
    vendingState = machine->getState();
    vendingState->chooseProduct(machine,102);

    vendingState = machine->getState();
    vendingState->dispenseProduct(machine,102);
//   vendingState->showState();
    DisplayInventory(machine);
    vendingState = machine->getState();
    vendingState->showState();

   vendingState->clickOnInsertCoinButton(machine);
    vendingState = machine->getState();
    vendingState->insertCoin(machine,Coin::TEN);
    vendingState->insertCoin(machine,Coin::TWENTY);
    vendingState->clickOnStartProductSelectionButton(machine);
// vendingState->showState();
    //SelectionState
    vendingState = machine->getState();
    vendingState->chooseProduct(machine,102);

    vendingState = machine->getState();
    vendingState->dispenseProduct(machine,102);
//   vendingState->showState();
    DisplayInventory(machine);

    return 0;
}

