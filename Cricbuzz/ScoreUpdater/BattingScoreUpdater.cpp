#include "BattingScoreUpdater.h"
#include "../Innings/Ball.h"

BattingScoreUpdater::BattingScoreUpdater(/* args */shared_ptr<Team>team):
ScoreUpdateObserver(team)
{
}

BattingScoreUpdater::~BattingScoreUpdater()
{
}

void BattingScoreUpdater::updateScore(shared_ptr<Ball>ballDetail)
{
    int playedBy = ballDetail->getPlayedBy();
    int bowledBy = ballDetail->getBowledBy();

    int four=0,six=0,runs=0,ball=0;

    if(ballDetail->getRunType()==RunType::FOUR)four++;
    else if(ballDetail->getRunType()==RunType::SIX)six++;
    //complete it 

}
