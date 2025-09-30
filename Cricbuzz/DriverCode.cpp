#include<bits/stdc++.h>
#include "Match.h"
#include "PlayerController.h"
#include "MatchType/MatchType.h"
#include "MatchType/T20.h"
using namespace std;

int main()
{
    cout<<"Happy Coding"<<endl;
    srand(time(0));
    auto playerController = PlayerController::getInstance();

    // --- Create Players for Team India ---
    auto p1 = make_shared<Player>(make_shared<Person>("Virat Kohli", 35), PlayerType::BATSMAN);
    auto p2 = make_shared<Player>(make_shared<Person>("Rohit Sharma", 37), PlayerType::BATSMAN);
    auto p3 = make_shared<Player>(make_shared<Person>("Hardik Pandya", 32), PlayerType::ALLAROUNDER);
    auto p4 = make_shared<Player>(make_shared<Person>("Jasprit Bumrah", 30), PlayerType::BOWLER);

    // Add players to controller
    playerController->addPlayer(p1);
    playerController->addPlayer(p2);
    playerController->addPlayer(p3);
    playerController->addPlayer(p4);

    // Create Team India
    auto teamIndia = make_shared<Team>("India", 5);  // T20 match
    teamIndia->addPlaying11(p1->getPlayerId(), PlayerType::BATSMAN);
    teamIndia->addPlaying11(p2->getPlayerId(), PlayerType::ALLAROUNDER);
    teamIndia->addPlaying11(p3->getPlayerId(), PlayerType::ALLAROUNDER);
    teamIndia->addPlaying11(p4->getPlayerId(), PlayerType::BOWLER);

    // --- Create Players for Team Australia ---
    auto p5 = make_shared<Player>(make_shared<Person>("David Warner", 36), PlayerType::BATSMAN);
    auto p6 = make_shared<Player>(make_shared<Person>("Steve Smith", 35), PlayerType::BATSMAN);
    auto p7 = make_shared<Player>(make_shared<Person>("Mitchell Marsh", 34), PlayerType::ALLAROUNDER);
    auto p8 = make_shared<Player>(make_shared<Person>("Mitchell Starc", 33), PlayerType::BOWLER);

    playerController->addPlayer(p5);
    playerController->addPlayer(p6);
    playerController->addPlayer(p7);
    playerController->addPlayer(p8);

    // Create Team Australia
    auto teamAustralia = make_shared<Team>("Australia", 5);
    teamAustralia->addPlaying11(p5->getPlayerId(), PlayerType::BATSMAN);
    teamAustralia->addPlaying11(p6->getPlayerId(), PlayerType::BATSMAN);
    teamAustralia->addPlaying11(p7->getPlayerId(), PlayerType::ALLAROUNDER);
    teamAustralia->addPlaying11(p8->getPlayerId(), PlayerType::BOWLER);

    //Matchtype
    shared_ptr<MatchType> matchType= make_shared<T20>();
    matchType->setOvers();

    Match match(teamIndia,teamAustralia,"29/09/2025","Mumbai",matchType);
    match.startMatch();
    
    return 0;
}