#pragma once
#include<memory>
using namespace std;
class Ball;
class Team;
class ScoreUpdateObserver
{
private:
    /* data */
    shared_ptr<Team>team;
public:
    ScoreUpdateObserver(/* args */shared_ptr<Team>team):
    team(team){}
    virtual ~ScoreUpdateObserver()=default;

    virtual void updateScore(shared_ptr<Ball>ballDetail)=0;
};
