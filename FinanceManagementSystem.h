#ifndef FINANCE_MANAGEMENT_SYSTEM_H
#define FINANCE_MANAGEMENT_SYSTEM_H

#include "Account.h"
#include "BudgetManager.h"
#include "Goal.h"
#include "Transaction.h"

#include <memory>
#include <string>
#include <vector>

using namespace std;

class FinanceManagementSystem {
private:
    vector<unique_ptr<Account>> accounts;
    vector<Transaction> transactions;
    vector<Goal> goals;
    BudgetManager budgetManager;
    const string storageFile = "finance_data.txt";

    Account* selectAccount();
    void recordTransaction(const string& accountName, TransactionType type,
                           const string& category, double amount,
                           const string& description);

public:
    FinanceManagementSystem();
    ~FinanceManagementSystem();

    void addAccount();
    void listAccounts() const;
    double netWorth() const;
    void deposit();
    void withdraw();
    void transferFunds();
    void manageBudget();
    void showBudget() const;
    void addGoal();
    void updateGoal();
    void listGoals() const;
    void showAnalytics() const;
    void saveData() const;
    void loadData();
    void run();
};

#endif
