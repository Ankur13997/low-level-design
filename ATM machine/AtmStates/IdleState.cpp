#include "IdleState.h"
#include "../Atm.h"
#include "../Card.h"
#include "States.h"
#include "HasCardState.h"

void IdleState::insertCard(shared_ptr<Atm> atm, shared_ptr<Card> card) 
{
    atm->setState(make_shared<HasCardState>());
}
void  IdleState::showState() 
{
    cout<<"Idle State"<<endl;
} 
