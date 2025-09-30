#pragma once
#include "Ball.h"
#include<vector>
#include "../Team.h"
class Over
{
private:
    /* data */
    int ballCount;
    vector<shared_ptr<Ball>>balls;
    int extraCount;
public:
    Over()
    {
        ballCount=0;
        extraCount=0;
    }
    ~Over(){}

    bool startOver(shared_ptr<Team>battingTeam,shared_ptr<Team>bowlingTeam,int runsToWin)
    {
        while(ballCount<=6)
        {
            shared_ptr<Ball> ball = make_shared<Ball>(ballCount+1);

            bool isValid = ball->startBallDelivery(battingTeam,bowlingTeam);

            if(isValid)
            {
                ballCount++;
                if(runsToWin!=-1 && battingTeam->getTotalRunScored() > runsToWin)
                {
                    battingTeam->setIsWinner(true);
                    return true;
                }

                if(ball->getBallType()==BallType::WICKET)
                {
                    int nextPlayer=battingTeam->getNextBatsman();
                    if (nextPlayer == -1) {
                            
                            return false;
                        }
                    battingTeam->setStriker(nextPlayer);
                }
            }
            else
            {
                extraCount++;
            }
            balls.push_back(ball);

        }
        return true;
    }
};


