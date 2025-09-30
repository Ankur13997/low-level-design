#pragma once
#include "PlayerType.h"
#include "Person.h"
#include<memory>
using namespace std;
class Player
{
private:
    /* data */
    int playerId;
    shared_ptr<Person> person;
    PlayerType playerType;
    static inline int idCounter=0;
public:

    Player(/* args */shared_ptr<Person> person,PlayerType playerType):
    playerId(++idCounter),person(person),playerType(playerType){}
    ~Player(){}

    int getPlayerId(){return playerId;}
};


