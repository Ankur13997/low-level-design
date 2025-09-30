#pragma once
#include "../Team.h"
#include "Over.h"
#include "../MatchType/MatchType.h"
class Inning
{
private:
    /* data */
    shared_ptr<Team> battingTeam;
    shared_ptr<Team> bowlingTeam;
    vector<shared_ptr<Over>>overs;
    shared_ptr<MatchType> matchType;
    int runsToWin;
public:
    Inning(/* args */shared_ptr<Team> battingTeam,shared_ptr<Team> bowlingTeam,shared_ptr<MatchType> matchType,int runsToWin):
    battingTeam(battingTeam),bowlingTeam(bowlingTeam),matchType(matchType),runsToWin(runsToWin){}

    ~Inning(){}

    void start()
    {
        int noOfOvers = matchType->getNoOfOvers();
        
        for(int over=1;over<=noOfOvers;over++)
        {
            shared_ptr<Over>currentOver=make_shared<Over>();
            bool isOverCompleted=currentOver->startOver(battingTeam,bowlingTeam,runsToWin);
            if(!isOverCompleted)
            {
                cout << "All out! Innings ends." << endl;
                return;
            }
            if(battingTeam->getIsWinner())
            {
                cout<<battingTeam->getTeamName()<<"'s Win"<<endl;
                return;
            }
            battingTeam->swapStriker();

        }

        if( runsToWin != -1 && battingTeam->getTotalRunScored()<runsToWin)
        {
            bowlingTeam->setIsWinner(true);
            return;
        }
    }

};

