#pragma once
#include "BalanceSheet.cpp"
#include "Expense.cpp"
#include "SplitFactory.cpp"
#include "Expense.cpp"
class ExpenseController
{
private:
    /* data */
 
    shared_ptr<BalanceSheet> balanceSheet;
public:
    ExpenseController(/* args */){
  
        balanceSheet=make_shared<BalanceSheet>();

    }
    ~ExpenseController(){}

    void createExpense(shared_ptr<User> paidByUser,double amount,vector<shared_ptr<Split>>&allSplits,SplitType type)
    {
        shared_ptr<ExpenseSplit> expenseSplit = SplitFactory::getSplit(type);
        bool isExpenseValid = expenseSplit->validate(allSplits,amount);
        
        if(!isExpenseValid)
        {
            cout<<"Expense creation failed."<<endl;
            return ;
        }
        shared_ptr<Expense> expense = make_shared<Expense>(paidByUser,amount,allSplits,type);
        balanceSheet->updateUserExpenseBalanceSheet(paidByUser,amount,allSplits);
        cout<<"Expense created successfull."<<endl;
    }

    shared_ptr<BalanceSheet> getBalanceSheet()
    {
        return balanceSheet;
    }
    
};

