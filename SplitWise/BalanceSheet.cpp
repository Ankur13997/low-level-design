#pragma once
#include<memory>
#include "User.cpp"
#include "Split.cpp"
#include<vector>
class BalanceSheet
{
private:
    /* data */
public:
    BalanceSheet(/* args */){}
    ~BalanceSheet(){}

    void updateUserExpenseBalanceSheet(shared_ptr<User> paidByUser,double amount,vector<shared_ptr<Split>>&allSplits)
    {
        int paidByUserId=paidByUser->getUserid();
        auto paidbyUserSheet = paidByUser->getUserSheet();
        for(auto split:allSplits)
        {
            shared_ptr<User> user = split->getUser();
            double owedMoney = split->getowedMoney();
            int userId = user->getUserid();
            if(user!=paidByUser)
            {
                auto userSheet=user->getUserSheet();
                userSheet->setOwed(paidByUserId,owedMoney);  

                paidbyUserSheet->setRecieve(userId,owedMoney);

            }


        }
    }

    void showBalanceofUser(shared_ptr<User> user)
    {
    if (!user || !user->getUserSheet()) {
        cout << "Invalid user or no balance sheet found.\n";
        return;
    }

    auto userSheet = user->getUserSheet()->getUserSheet();
    if (userSheet.empty()) {
        cout << "No balances for user: " << user->getUserName() << endl;
        return;
    }

    cout << "Balances for user: " << user->getUserName() << endl;
    for (const auto& [otherUserId, balance] : userSheet) {
        if (balance.owed > 0) {
            cout << "You owe User " << otherUserId << ": " << balance.owed << endl;
        }
        if (balance.recieve > 0) {
            cout << "User " << otherUserId << " owes you: " << balance.recieve << endl;
        }
    }
}

};


