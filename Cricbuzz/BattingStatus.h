#pragma once

class BattingStatus
{
private:
    int ballsPlayed;
    int runScored;
    int four;
    int six;
    double strikeRate;
    int wicketBy;

public:
    BattingStatus() 
        : ballsPlayed(0), runScored(0), four(0), six(0), strikeRate(0.0),wicketBy(-1) {}
    ~BattingStatus() {}

    // Getter methods
    int getBallsPlayed() const { return ballsPlayed; }
    int getRunScored() const { return runScored; }
    int getFour() const { return four; }
    int getSix() const { return six; }
    double getStrikeRate() const { return strikeRate; }
    int getWicketBy()const {return wicketBy;}

    void setWicketBy(int playerId) {wicketBy = playerId;}
    
    // Common function to update stats
    void updateStats(int balls, int runs, int fours, int sixes) {
        ballsPlayed += balls;
        runScored += runs;
        four += fours;
        six += sixes;
        strikeRate = (ballsPlayed > 0) ? (static_cast<double>(runScored) * 100.0 / ballsPlayed) : 0.0;
    }
};
