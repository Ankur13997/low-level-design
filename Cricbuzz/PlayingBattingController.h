#pragma once
#include "Player.h"
#include<queue>
#include <algorithm>
#include<iostream>
class PlayingBattingController
{
private:
    /* data */
    queue<int>yetToPlay;
    int striker;
    int nonStriker;
public:
    PlayingBattingController(/* args */){}
    ~PlayingBattingController(){}

    void addPlayer(int playerId){yetToPlay.push(playerId);}
    void setStriker(int playerId){striker=playerId;}
    void setNonStriker(int playerId){nonStriker=playerId;}
    
    void swapStriker()
    {
        swap(striker,nonStriker);
    }
    int getNextPlayer() {
        if (yetToPlay.empty()) {
            cout << " No batsmen left!" << endl;
            return -1; // sentinel for "all out"
        }
        int currPlayer = yetToPlay.front();
        yetToPlay.pop();
        return currPlayer;
    }

    bool isPlayerLeft()
    {
        return !yetToPlay.empty();
    }

    int getStriker(){return striker;}
    int getNonStriker(){return nonStriker;}

   

};


