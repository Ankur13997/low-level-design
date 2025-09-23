#include <bits/stdc++.h>
#include "Atm.h"
#include "AtmStates/States.h"
#include "User.h"
using namespace std;

int main() {
    shared_ptr<Atm> atm = make_shared<Atm>();

    // Users and accounts
    shared_ptr<BankAccount> account1 = make_shared<BankAccount>(1000, "ABC");
    shared_ptr<BankAccount> account2 = make_shared<BankAccount>(50000, "XYZ");
    shared_ptr<Card> card1 = make_shared<Card>("123456789", 123, 1234, "ABC", account1);
    shared_ptr<Card> card2 = make_shared<Card>("987654321", 321, 4321, "XYZ", account2);

    shared_ptr<User> user1 = make_shared<User>(card1, account1);
    shared_ptr<User> user2 = make_shared<User>(card2, account2);

    auto atmState = atm->getState();

    cout << "\n--- Test Case 1: Successful small withdrawal ---\n";
    atmState->insertCard(atm, card1);
    atmState = atm->getState();
    atmState->authenticatePin(atm, card1, 1234);
    atmState = atm->getState();
    atmState->selectOperation(atm, card1, CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, card1, 500);

    cout << "\n--- Test Case 2: Withdrawal using multiple denominations ---\n";
    atmState->selectOperation(atm, card1, CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, card1, 3800);

    cout << "\n--- Test Case 3: Withdrawal exceeding ATM notes ---\n";
    atmState->selectOperation(atm, card2, CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, card2, 20000);

    cout << "\n--- Test Case 4: Withdrawal exceeding account balance ---\n";
    atmState->selectOperation(atm, card1, CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, card1, 2000);

    cout << "\n--- Test Case 5: Invalid PIN ---\n";
    atmState->insertCard(atm, card1);
    atmState = atm->getState();
    atmState->authenticatePin(atm, card1, 1111);

    cout << "\n--- Test Case 6: Display balance ---\n";
    atmState->insertCard(atm, card2);
    atmState = atm->getState();
    atmState->authenticatePin(atm, card2, 4321);
    atmState = atm->getState();
    atmState->selectOperation(atm, card2, DISPLAYAMOUNT);
    atmState = atm->getState();
    atmState->displayBalance(atm, card2);

    cout << "\n--- Test Case 7: Multiple withdrawals ---\n";
    atmState->selectOperation(atm, card2, CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, card2, 3800); // Should succeed
    atmState->selectOperation(atm, card2, CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, card2, 15000); // Should fail

    cout << "\n--- Test Case 8: Withdraw exact amount with smallest notes ---\n";
    // Manually empty 2000 notes to simulate
    atm->updatetwo(0); 
    atmState->selectOperation(atm, card2, CASHWITHDRAW);
    atmState = atm->getState();
    atmState->cashWithdrawal(atm, card2, 1500); // 3x500 notes

    return 0;
}
