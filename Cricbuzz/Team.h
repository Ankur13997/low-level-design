#pragma once
#include "Player.h"
#include "PlayingBattingController.h"
#include "PlayingBowlingController.h"
#include "BowlingStatus.h"
#include "BattingStatus.h"
#include<iostream>
class Team
{
private:
    /* data */
    string teamName;
    queue<int>playing11;
    queue<int>bench;
    int totalRunScored;
    bool isWinner;
    shared_ptr<PlayingBattingController>battingController;
    shared_ptr<PlayingBowlingController>bowlingController;
    unordered_map<int,shared_ptr<BattingStatus>>battingStatus;
    unordered_map<int,shared_ptr<BowlingStatus>>bowlingStatus;
public:
    Team(/* args */string teamName,int allowedOvers):
    teamName(teamName){
        totalRunScored=0;
        isWinner=false;
        battingController=make_shared<PlayingBattingController>();
        bowlingController=make_shared<PlayingBowlingController>(allowedOvers);
    }
    ~Team(){}
    string getTeamName(){return teamName;}
    bool getIsWinner(){return isWinner;}
    void setIsWinner(bool value){isWinner=value;}
    void updateTotalRunScored(int run){totalRunScored+=run;}
    void addPlaying11(int playerId,PlayerType type)
    {
        playing11.push(playerId);
        addPlayerStatus(playerId);
        if(type==PlayerType::BATSMAN || type ==PlayerType::ALLAROUNDER)
            battingController->addPlayer(playerId);
        if(type==PlayerType::BOWLER || type ==PlayerType::ALLAROUNDER)
            bowlingController->addBowler(playerId);
    }
    void addBenchPlayer(int playerId)
    {
        bench.push(playerId);
    }

    void addPlayerStatus(int playerId) {
        battingStatus[playerId] = make_shared<BattingStatus>();
        bowlingStatus[playerId] = make_shared<BowlingStatus>();
    }

    int getTotalRunScored(){return totalRunScored;}
    // Batsman Controller
    int getNextBatsman()
    {
        return battingController->getNextPlayer();
    }

    void setStrikerNonStriker(int striker,int nonStriker)
    {
        battingController->setStriker(striker);
        battingController->setNonStriker(nonStriker);
    }

    void swapStriker()
    {
        battingController->swapStriker();
    }

    bool isPlayerLeft()
    {
        return battingController->isPlayerLeft();
    }
    void setStriker(int playerId){
         battingController->setStriker(playerId);
    }

    int getStriker(){return battingController->getStriker();}
    int getNonStriker(){return battingController->getNonStriker();}

    //Bowling Controller
    void setCurrentBowler(int playerId)
    {
       bowlingController->setCurrentBowler(playerId);
    }
    int getCurrentBowler(){return bowlingController->getCurrentBowler();}
    int getNextBowler(){return bowlingController->getNextBowler();}


    // Stats Update
    void updateBattingStatus(int playerId,int balls, int runs, int fours, int sixes)
    {
        if(battingStatus.count(playerId)==0)
        {
            cout<<"Invalid Player"<<endl;
            return;
        }
        totalRunScored+=runs;
        auto &status = battingStatus[playerId];
        status->updateStats(balls, runs,fours,sixes);

    }

    void updateBowlingStatus(int playerId,double ov, int r, int w, int e)
    {
        if(bowlingStatus.count(playerId)==0)
        {
            cout<<"Invalid Player"<<endl;
            return;
        }
        auto &status= bowlingStatus[playerId];
        status->updateStats(ov,r,w,e);
    }

    void displayPlayerStats() {
        cout << "Stats for Team: " << teamName << endl;

        cout << "\nBatting Stats:\n";
        for (auto &entry : battingStatus) {
            int playerId = entry.first;
            auto status = entry.second;
            cout << "Player " << playerId
                << " -> Runs: " << status->getRunScored()
                << ", Balls: " << status->getBallsPlayed()
                << ", Fours: " << status->getFour()
                << ", Sixes: " << status->getSix()
                << ", SR: " << status->getStrikeRate()
                << endl;
        }

        cout << "\nBowling Stats:\n";
        for (auto &entry : bowlingStatus) {
            int playerId = entry.first;
            auto status = entry.second;
            cout << "Player " << playerId
                << " -> Overs: " << status->getOvers()
                << ", Runs: " << status->getRuns()
                << ", Wickets: " << status->getWickets()
                << ", Extras: " << status->getExtra()
                << ", Econ: " << status->getEconomy()
                << endl;
        }
    }

    

};


