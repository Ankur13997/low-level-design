#pragma once
#include "ExpenseController.cpp"
#include "UserController.cpp"
#include "GroupController.cpp"
#include "BalanceSheet.cpp"


class Splitwise
{
private:
    /* data */
    shared_ptr<UserController> userController;
    shared_ptr<ExpenseController>expenseController;
    shared_ptr<BalanceSheet>balanceSheet;
    shared_ptr<GroupController>groupController;
public:
    Splitwise(/* args */)
    {
        userController=make_shared<UserController>();
        expenseController=make_shared<ExpenseController>();
        balanceSheet=make_shared<BalanceSheet>();
        groupController=make_shared<GroupController>();

        Initialize();
    }
    ~Splitwise(){}

    void Initialize()
    {
        vector<shared_ptr<User>>allUsers=createUser();
        for(auto user:allUsers)
        {
            cout<<user->getUserid()<<" "<<user->getUserName()<<endl;
        }
    }
    vector<shared_ptr<User>>createUser()
    {
        vector<shared_ptr<User>>allUser;
        for(int i=0;i<5;i++)
        {
            string name="Name"+to_string(i+1);
            string phone=to_string(i+1);
            string email="email"+to_string(i+1)+"@gmail.com";
            allUser.emplace_back(make_shared<User>(name,phone,email));
        }
        return allUser;
    }
};


