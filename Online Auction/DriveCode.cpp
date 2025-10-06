/*
Mediator pattern:
It can also use in :
1) Chat application 
2) Airline Management System

*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
// Forward declarations
class IColleague;
class IMediator;

// Mediator interface
class IMediator {
public:
    virtual void addBidder(shared_ptr<IColleague> bidder) = 0;
    virtual void placeBid(const string& bidderName, int amount) = 0;
    virtual ~IMediator() = default;
};

// Colleague interface
class IColleague {
protected:
    shared_ptr<IMediator> mediator;
    string name;

public:
    IColleague(shared_ptr<IMediator> med, const string& n)
        : mediator(med), name(n) {}

    virtual void placeBid(int amount) = 0;
    virtual void receiveBidNotification(const string& bidderName, int amount) = 0;
    string getName() const { return name; }
    virtual ~IColleague() = default;
};

// Concrete Mediator
class AuctionMediator : public IMediator {
private:
    vector<shared_ptr<IColleague>> bidders;

public:
    void addBidder(shared_ptr<IColleague> bidder) override {
        bidders.push_back(bidder);
    }

    void placeBid(const string& bidderName, int amount) override {
        cout << "\n[AuctionMediator]: " << bidderName 
                  << " placed a bid of $" << amount << "\n";
        notifyBidders(bidderName, amount);
    }

private:
    void notifyBidders(const string& bidderName, int amount) {
        for (auto& b : bidders) {
            if (b->getName() != bidderName)
                b->receiveBidNotification(bidderName, amount);
        }
    }
};

// Concrete Colleague
class Bidder : public IColleague {
public:
    Bidder(shared_ptr<IMediator> med, const string& n)
        : IColleague(med, n) {}

    void placeBid(int amount) override {
        mediator->placeBid(name, amount);
    }

    void receiveBidNotification(const string& bidderName, int amount) override {
        cout << name << " received notification: " << bidderName
                  << " placed a bid of $" << amount << "\n";
    }
};

// Client
int main() {
    auto auctionMediator = make_shared<AuctionMediator>();

    auto alice = make_shared<Bidder>(auctionMediator, "Alice");
    auto bob = make_shared<Bidder>(auctionMediator, "Bob");
    auto charlie = make_shared<Bidder>(auctionMediator, "Charlie");

    auctionMediator->addBidder(alice);
    auctionMediator->addBidder(bob);
    auctionMediator->addBidder(charlie);

    alice->placeBid(100);
    bob->placeBid(150);
    charlie->placeBid(200);

    return 0;
}
