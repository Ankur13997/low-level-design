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

    shared_ptr<Expense> createExpense(shared_ptr<User> paidByUser,double amount,vector<shared_ptr<Split>>&allSplits,SplitType type)
    {
        shared_ptr<ExpenseSplit> expenseSplit = SplitFactory::getSplit(type);
        bool isExpenseValid = expenseSplit->validate(allSplits,amount);
        
        if(!isExpenseValid)
        {
            cout<<"Expense creation failed."<<endl;
            return nullptr ;
        }
        shared_ptr<Expense> expense = make_shared<Expense>(paidByUser,amount,allSplits,type);
        balanceSheet->updateUserExpenseBalanceSheet(paidByUser,amount,allSplits);
        cout<<"Expense created successfull."<<endl;
        return expense;
    }

    shared_ptr<BalanceSheet> getBalanceSheet()
    {
        return balanceSheet;
    }
    
};

