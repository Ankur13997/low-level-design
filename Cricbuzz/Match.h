#pragma once
#include "Team.h"
#include "Innings/Inning.h"
#include "MatchType/MatchType.h"
#include <ctime>
#include <iostream>
using namespace std;

class Match
{
private:
    shared_ptr<Team> teamA, teamB;
    string date;
    string venue;
    vector<shared_ptr<Inning>> innings;
    shared_ptr<MatchType> matchType;
    shared_ptr<Team> tossWinner;
    int noOfOvers;

public:
    Match(shared_ptr<Team> teamA, shared_ptr<Team> teamB, string date, string venue, shared_ptr<MatchType> matchType)
        : teamA(teamA), teamB(teamB), date(date), venue(venue), matchType(matchType)
    {
        cout << "Match scheduled between " << teamA->getTeamName()
             << " and " << teamB->getTeamName()
             << " at " << venue << " on " << date << "." << endl;

        findTossWinner();
        noOfOvers = matchType->getNoOfOvers();
        cout << "Match type: " << matchType->getName()
             << " (" << noOfOvers << " overs)." << endl;
    }

    ~Match() {}

    // --- Toss ---
    bool toss()
    {
        int val = rand() % 10;
        return val < 5;
    }

    void findTossWinner()
    {
        if (toss())
            tossWinner = teamA;
        else
            tossWinner = teamB;

        cout << tossWinner->getTeamName() << " won the toss." << endl;
    }

    shared_ptr<Team> findNextInning()
    {
        return (tossWinner == teamA) ? teamB : teamA;
    }

    // --- Start Match ---
    void startMatch()
    {
        cout << "\n--- Match Started ---" << endl;

        shared_ptr<Team> battingTeam = tossWinner;
        shared_ptr<Team> bowlingTeam = findNextInning();

        cout << battingTeam->getTeamName() << " will bat first." << endl;
        cout << bowlingTeam->getTeamName() << " will bowl first." << endl;

        // First Inning
        shared_ptr<Inning> firstInning = make_shared<Inning>(battingTeam, bowlingTeam, matchType, -1);
        cout << "\n--- First Inning Begins ---" << endl;
        firstInning->start();

        int runScored = battingTeam->getTotalRunScored();
        cout << "End of first innings. " << battingTeam->getTeamName()
             << " scored " << runScored << " runs." << endl;

        // Second Inning
        cout << "\n--- Second Inning Begins ---" << endl;
        shared_ptr<Inning> secondInning = make_shared<Inning>(bowlingTeam, battingTeam, matchType, runScored);
        secondInning->start();

        cout << "End of second innings. " << bowlingTeam->getTeamName()
             << " scored " << bowlingTeam->getTotalRunScored() << " runs." << endl;

        innings.push_back(firstInning);
        innings.push_back(secondInning);

        if(bowlingTeam->getTotalRunScored() == battingTeam->getTotalRunScored())
        {
            cout<<endl<<"Match Tie"<<endl;
        }
        else if(!bowlingTeam->getIsWinner())
        {
            cout<<battingTeam->getTeamName()<<"'s win"<<endl;
        }
        cout << "\n--- Match Ended ---" << endl;
    }

    // --- Getters ---
    shared_ptr<Team> getTeamA() const { return teamA; }
    shared_ptr<Team> getTeamB() const { return teamB; }
    string getDate() const { return date; }
    string getVenue() const { return venue; }
    shared_ptr<MatchType> getMatchType() const { return matchType; }
    shared_ptr<Team> getTossWinner() const { return tossWinner; }
    int getNoOfOvers() const { return noOfOvers; }
    const vector<shared_ptr<Inning>>& getInnings() const { return innings; }

    // --- Setters ---
    void setDate(const string &d) { date = d; }
    void setVenue(const string &v) { venue = v; }
    void setMatchType(shared_ptr<MatchType> mt) { matchType = mt; noOfOvers = mt->getNoOfOvers(); }
};
