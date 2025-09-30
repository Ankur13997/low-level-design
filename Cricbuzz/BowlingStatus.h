#pragma once

class BowlingStatus
{
private:
    double overs;   // Overs bowled (can be fractional, e.g., 4.3 = 4 overs 3 balls)
    int runs;       // Runs conceded
    int wickets;    // Wickets taken
    int extra;      // Extras conceded
    double economy; // Economy rate

public:
    BowlingStatus()
        : overs(0.0), runs(0), wickets(0), extra(0), economy(0.0) {}
    ~BowlingStatus() {}

    // Getter methods
    double getOvers() const { return overs; }
    int getRuns() const { return runs; }
    int getWickets() const { return wickets; }
    int getExtra() const { return extra; }
    double getEconomy() const { return economy; }

    // Common update function
    void updateStats(double ov, int r, int w, int e) {
        overs += ov;
        runs += r;
        wickets += w;
        extra += e;
        economy = (overs > 0.0) ? (static_cast<double>(runs) / overs) : 0.0;
    }
};
