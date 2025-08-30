
#include "User.cpp"
#include "Expense.cpp"
#include "ExpenseController.cpp"

class Group
{
private:
    /* data */
    int groupId;
    string groupName;
    shared_ptr<User> createdBy;
    vector<shared_ptr<Expense>>allExpenses;
    vector<shared_ptr<User>>allUsers;
    shared_ptr<ExpenseController>expenseController;
public:
    static inline int counterId=0;
    Group(string groupName, shared_ptr<User> createdBy):
    groupId(++counterId),groupName(groupName),createdBy(createdBy)
    {
        expenseController=make_shared<ExpenseController>();
        allUsers=vector<shared_ptr<User>>();
        allExpenses=vector<shared_ptr<Expense>>();
    }

    ~Group(){}

    int getGroupId(){return groupId;}
    vector<shared_ptr<Expense>>getAllExpenses(){return allExpenses;}
    vector<shared_ptr<User>>getallUsers(){return allUsers;}
    shared_ptr<ExpenseController>getExpenseController(){return expenseController;}
    void addUser(shared_ptr<User>user){
        allUsers.push_back(user);
    }
    void addExpense(shared_ptr<Expense>expense)
    {
        allExpenses.push_back(expense);
    }

    void createExpense(shared_ptr<User> paidByUser,double amount,vector<shared_ptr<Split>>&allSplits,SplitType type)
    {
        auto expense = expenseController->createExpense(paidByUser,amount,allSplits,type);
        addExpense(expense);
    }


};
