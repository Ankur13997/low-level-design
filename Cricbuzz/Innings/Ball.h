#pragma once
#include "BallType.h"
#include "RunType.h"
#include <stdlib.h>
#include <ctime>
#include <memory>
#include "../ScoreUpdater/ScoreUpdateObserver.h"
#include "../ScoreUpdater/BattingScoreUpdater.h"
using namespace std;
class Over;
class Team;
class Ball
{
private:
    /* data */
    int ballNumber;
    BallType ballType;
    RunType runType;
    int playedBy;
    int bowledBy;
    //vector<shared_ptr<ScoreUpdateObserver>>scoreUpdater;
public:
    Ball(int ballNumber):ballNumber(ballNumber){
    //    scoreUpdater.push_back()
    }

    ~Ball(){}

    bool startBallDelivery(shared_ptr<Team>battingTeam,shared_ptr<Team>bowlingTeam);
    BallType getBallType();
    RunType getRunType();
    int getPlayedBy(){return playedBy;}
    int getBowledBy(){return bowledBy;}
    void setPlayedBy(int playerId){playedBy=playerId;}
    void setBowledBy(int playerId){bowledBy = playerId;}
};
