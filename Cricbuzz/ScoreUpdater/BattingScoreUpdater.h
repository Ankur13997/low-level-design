#pragma once
#include "ScoreUpdateObserver.h"

class BattingScoreUpdater : public ScoreUpdateObserver
{
private:
    /* data */

public:
    BattingScoreUpdater(/* args */shared_ptr<Team>team);
    ~BattingScoreUpdater();
    void updateScore(shared_ptr<Ball>ballDetail)override;
};
