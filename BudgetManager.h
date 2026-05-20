#ifndef BUDGET_MANAGER_H
#define BUDGET_MANAGER_H

#include <string>
#include <vector>

using namespace std;

struct ExpenseItem {
    string name;
    string category;
    double amount;
};

class BudgetManager {
private:
    vector<ExpenseItem> expenses;

public:
    void addExpense(const string& name, const string& category, double amount);
    double totalExpenses() const;
    double disposableIncome(double netWorth) const;
    const vector<ExpenseItem>& getExpenses() const;
    void display(double netWorth) const;
};

#endif
