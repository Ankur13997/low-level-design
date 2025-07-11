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
};


