#include "Ball.h"
#include "../Team.h"

#include "Ball.h"
#include "../Team.h"
#include <iostream>
using namespace std;

bool Ball::startBallDelivery(shared_ptr<Team> battingTeam, shared_ptr<Team> bowlingTeam)
{
    ballType = getBallType();
    playedBy = battingTeam->getStriker();
    bowledBy = bowlingTeam->getCurrentBowler();

    cout << "Ball delivered: ";

    if (ballType == BallType::EXTRA)
    {
        //notifyObserver(this);
        runType = RunType::ONE;
        cout << "Extra ball! 1 run awarded.\n";
        battingTeam->updateTotalRunScored(1);
        return false;  // ball not counted
    }
    else if (ballType == BallType::NORMAL)
    {
        runType = getRunType();
        int run=0;
        switch (runType)
        {
            case RunType::ONE:
                cout << "1 run\n";
                run=1;
                battingTeam->swapStriker();
                break;
            case RunType::TWO:
                cout << "2 runs\n";
                run=2;
                break;
            case RunType::THREE:
                cout << "3 runs (striker changes)\n";
                run=3;
                battingTeam->swapStriker();
                break;
            case RunType::FOUR:
                cout << "FOUR!\n";
                run=4;
                break;
            case RunType::SIX:
                cout << "SIX!\n";
                run=6;
                break;
            default:
                cout << "0 run\n";
                break;
        }
        battingTeam->updateTotalRunScored(run);
        
    }
    else if (ballType == BallType::WICKET)
    {
        runType = RunType::ZERO;
        battingTeam->updateTotalRunScored(0);
        cout << "WICKET!\n";
    }
   // notifyObserver(this);
    return true; // valid ball
}

// void notifyObserver(shared_ptr<Ball>ball)
// {
//     for(auto observer : scoreUpdater)
//     {
//         observer.update(ball);
//     }
// }
BallType Ball::getBallType()
{
    int random =rand()%10;
    if(random<7)return BallType::NORMAL;
    else if(random<8)return BallType::WICKET;
    return BallType::EXTRA; 
}

RunType Ball::getRunType()
{
    int random = rand()%20;
    if(random<7)return RunType::ONE;
    else if(random<11)return RunType::TWO;
    else if(random<14)return RunType::THREE;
    else if(random<17)return RunType::FOUR;
    return RunType::SIX;
    
}

bool isWicketTaken()
{
    int random=rand()%10;
    if(random<2)return true;
    return false;
}