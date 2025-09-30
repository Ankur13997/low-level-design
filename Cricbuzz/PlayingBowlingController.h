#pragma once
#include "Player.h"
#include<deque>
#include<unordered_map>
class PlayingBowlingController
{
private:
    /* data */
    deque<int>bowlers;
    int currentBowler;
    unordered_map<int,int>playerVsAllowedOvers;
    int maxAllowedOvers;
public:
    PlayingBowlingController(/* args */int maxAllowedOvers):
    maxAllowedOvers(maxAllowedOvers){}
    ~PlayingBowlingController(){}

    void setCurrentBowler(int playerId)
    {
        currentBowler=playerId;
    }
    void addBowler(int playerId)
    {
        bowlers.push_back(playerId);
        playerVsAllowedOvers[playerId]=0;
    }

    int getCurrentBowler(){return currentBowler;}
    int getNextBowler()
    {
        int bowlerCount=bowlers.size();
        while(bowlerCount--)
        {
            int currBowler = bowlers.front();
            bowlers.pop_front();
            bowlers.push_back(currBowler);
            int overBowled=playerVsAllowedOvers[currBowler];
            if(overBowled<maxAllowedOvers)
            {
                playerVsAllowedOvers[currBowler]++;
                setCurrentBowler(currBowler);
                return currBowler;
            }
        }
        return -1;

    }

};
