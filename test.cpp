#include <iostream>
#include <thread>
#include <mutex>
#include<memory>
using namespace std;

class BankAccount {
private:
    int balance;
    mutex mtx;

public:
    BankAccount(int initialBalance) : balance(initialBalance) {}

    void withdraw(int amount, const string& user) {
        lock_guard<mutex> lock(mtx); // Lock access

        if (balance >= amount) {
            cout << user << " is withdrawing " << amount << "\n";
            balance -= amount;
            cout << user << " successfully withdrew. Balance left: " << balance << "\n";
        } else {
            cout << user << " tried to withdraw " << amount << " but insufficient funds!\n";
        }
    }

    int getBalance() {
        lock_guard<mutex> lock(mtx);
        return balance;
    }
};
void processWithdraw(shared_ptr<BankAccount>account, int amount, string user)
{
    account->withdraw(amount, user);
}
int main() {
    // BankAccount account(100); // Initial balance
    shared_ptr<BankAccount>account = make_shared<BankAccount>(100);
    thread t1(processWithdraw, account, 50, "user1");
    thread t2(processWithdraw, account, 30, "user2");

    thread t3(processWithdraw, account, 20, "user3");



    t1.join();
    t2.join();
    t3.join();

    cout << "Final Balance: " << account->getBalance() << endl;
    return 0;
}
