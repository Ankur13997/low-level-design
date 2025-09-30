#pragma once
#include "Player.h"
#include<unordered_map>
#include <mutex>
#include<iostream>
using namespace std;
class PlayerController
{
private:
    /* data */
    unordered_map<int,shared_ptr<Player>>playerController;
    inline static shared_ptr<PlayerController> instance=nullptr;
    
    PlayerController(){

    }
    inline static mutex mtx;

    PlayerController(const PlayerController&) = delete;
    PlayerController& operator=(const PlayerController&) = delete;
public:
    static shared_ptr<PlayerController>getInstance()
    {
        lock_guard<mutex>lock(mtx);
        if(!instance)
        {
            
            instance = shared_ptr<PlayerController>(new PlayerController());
        }
        return instance;
    }
    ~PlayerController(){}

    void addPlayer(const shared_ptr<Player>&player)
    {
        playerController[player->getPlayerId()]=player;
    }

    shared_ptr<Player>getPlayerById(int playerId)
    {
        if(playerController.count(playerId)==0)
        {
            cout<<"Invalid Id"<<endl;
            return nullptr;
        }
        return playerController[playerId];
    }


};
