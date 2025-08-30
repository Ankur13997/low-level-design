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
    // void demo()
    // {
    //     shared_ptr<Group>group=groupController->getGroupById(1);
    //     auto paidBy = userController->getUserbyId(1);

    //     vector<shared_ptr<Split>>allSplits=createSplits();
    //     group->createExpense(paidBy,100,allSplits,EQUAL);

    //     balanceSheet->showBalanceofUser(paidBy);
    // }
    void demo()
{
    // CASE 1: Group expense with EQUAL split
    shared_ptr<Group> group = groupController->getGroupById(1);
    auto paidBy = userController->getUserbyId(1);
    vector<shared_ptr<Split>> allSplits = createSplits(25, {1, 2, 3, 4});
    group->createExpense(paidBy, 100, allSplits, EQUAL);

    cout << "---- After Group EQUAL Split ----" << endl;
    showAllBalances();

    // CASE 2: Group expense with EXACT split
    vector<shared_ptr<Split>> exactSplits = {
        make_shared<Split>(userController->getUserbyId(1), 10),
        make_shared<Split>(userController->getUserbyId(2), 20),
        make_shared<Split>(userController->getUserbyId(3), 30),
        make_shared<Split>(userController->getUserbyId(4), 40)
    };
    group->createExpense(paidBy, 100, exactSplits, EXACT);

    cout << "---- After Group EXACT Split ----" << endl;
    showAllBalances();

    // CASE 3: Group expense with PERCENTAGE split
    vector<shared_ptr<Split>> percentageSplits = {
        make_shared<Split>(userController->getUserbyId(1), 10),
        make_shared<Split>(userController->getUserbyId(2), 20),
        make_shared<Split>(userController->getUserbyId(3), 30),
        make_shared<Split>(userController->getUserbyId(4), 40)
    };
    group->createExpense(paidBy, 100, percentageSplits, PERCENTAGE);

    cout << "---- After Group PERCENTAGE Split ----" << endl;
    showAllBalances();

    // CASE 4: Non-group expense (split between 2 users)
    auto u1 = userController->getUserbyId(1);
    auto u5 = userController->getUserbyId(5);
    vector<shared_ptr<Split>> nonGroupSplit = {
        make_shared<Split>(u1, 50),
        make_shared<Split>(u5, 50)
    };
    expenseController->createExpense(u1, 100, nonGroupSplit, EQUAL);

    cout << "---- After Non-group Expense ----" << endl;
    showAllBalances();
}
 vector<shared_ptr<Split>> createSplits(double amount, vector<int> userIds)
{
    vector<shared_ptr<Split>> allSplits;
    for (int id : userIds)
    {
        allSplits.emplace_back(make_shared<Split>(userController->getUserbyId(id), amount));
    }
    return allSplits;
}

void showAllBalances()
{
    for (int i = 1; i <= 5; ++i)
    {
        auto user = userController->getUserbyId(i);
        balanceSheet->showBalanceofUser(user);
    }
    cout << "---------------------------------\n";
}

           
    vector<shared_ptr<Split>>createSplits()
    {
        vector<shared_ptr<Split>>allsplits;
        allsplits.emplace_back(make_shared<Split>(userController->getUserbyId(1),25));
        allsplits.emplace_back(make_shared<Split>(userController->getUserbyId(2),25));
        allsplits.emplace_back(make_shared<Split>(userController->getUserbyId(3),25));
        allsplits.emplace_back(make_shared<Split>(userController->getUserbyId(4),25));
        return allsplits;
    }
    void Initialize()
    {
        createUser();
        createGroup();
        
    }
    void createGroup()
    {
        shared_ptr<User>createdBy=userController->getUserbyId(1);
        string name = "Group1";
        shared_ptr<Group>group=make_shared<Group>(name,createdBy);
        group->addUser(userController->getUserbyId(1));
        group->addUser(userController->getUserbyId(2));
        group->addUser(userController->getUserbyId(3));
        group->addUser(userController->getUserbyId(4));

        groupController->addGroup(group);
    }
    void createUser()
    {
       
        for(int i=0;i<5;i++)
        {
            string name="Name"+to_string(i+1);
            string phone=to_string(i+1);
            string email="email"+to_string(i+1)+"@gmail.com";
            shared_ptr<User>user=make_shared<User>(name,phone,email);
            userController->addUser(user);
        }
        return ;
    }
};


