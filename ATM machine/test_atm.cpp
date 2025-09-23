#include <gtest/gtest.h>
#include "Atm.h"
#include "AtmStates/States.h"
#include "User.h"
#include <memory>

using namespace std;

// Helper function to create a new ATM session
shared_ptr<Atm> createATM() {
    return make_shared<Atm>();
}

// Helper function to create a user with balance
shared_ptr<User> createUser(int balance, const string& name, const string& cardNum, int pin) {
    auto account = make_shared<BankAccount>(balance, name);
    auto card = make_shared<Card>(cardNum, 0, pin, name, account);
    return make_shared<User>(card, account);
}

TEST(ATMTests, SuccessfulSmallWithdrawal) {
    auto atm = createATM();
    auto user = createUser(5000, "ABC", "123456", 1234);

    auto atmState = atm->getState();
    atmState->insertCard(atm, user->getCard());
    atmState = atm->getState();
    atmState->authenticatePin(atm, user->getCard(), 1234);
    atmState = atm->getState();
    atmState->selectOperation(atm, user->getCard(), CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, user->getCard(), 500);

    // Check balances
    EXPECT_EQ(user->getCard()->getBankAccount()->getBalance(), 4500);
    EXPECT_EQ(atm->getAmount(), 19500);
}

TEST(ATMTests, InsufficientAccountBalance) {
    auto atm = createATM();
    auto user = createUser(1000, "ABC", "123456", 1234);

    auto atmState = atm->getState();
    atmState->insertCard(atm, user->getCard());
    atmState = atm->getState();
    atmState->authenticatePin(atm, user->getCard(), 1234);
    atmState = atm->getState();
    atmState->selectOperation(atm, user->getCard(), CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, user->getCard(), 2000);

    // Should fail, balances unchanged
    EXPECT_EQ(user->getCard()->getBankAccount()->getBalance(), 1000);
    EXPECT_EQ(atm->getAmount(), 20000);
}

TEST(ATMTests, InsufficientATMNotes) {
    auto atm = createATM();
    auto user = createUser(50000, "XYZ", "987654", 4321);

    // Empty 2000 notes to simulate insufficient notes
    atm->updatetwo(0);

    auto atmState = atm->getState();
    atmState->insertCard(atm, user->getCard());
    atmState = atm->getState();
    atmState->authenticatePin(atm, user->getCard(), 4321);
    atmState = atm->getState();
    atmState->selectOperation(atm, user->getCard(), CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, user->getCard(), 20000);

    // Should fail, balances unchanged
    EXPECT_EQ(user->getCard()->getBankAccount()->getBalance(), 50000);
    EXPECT_EQ(atm->getAmount(), 20000); 
}
