#include "BudgetManager.h"

#include <iomanip>
#include <iostream>

using namespace std;

void BudgetManager::addExpense(const string& name, const string& category, double amount) {
    expenses.push_back({name, category, amount});
}

double BudgetManager::totalExpenses() const {
    double total = 0;
    for (const auto& expense : expenses) {
        total += expense.amount;
    }
    return total;
}

double BudgetManager::disposableIncome(double netWorth) const {
    return netWorth - totalExpenses();
}

const vector<ExpenseItem>& BudgetManager::getExpenses() const {
    return expenses;
}

void BudgetManager::display(double netWorth) const {
    cout << "\nBudget Summary\n";
    cout << left << setw(25) << "Expense"
         << setw(24) << "Category"
         << "Amount\n";
    cout << string(60, '-') << '\n';

    for (const auto& expense : expenses) {
        cout << left << setw(25) << expense.name
             << setw(24) << expense.category
             << fixed << setprecision(2) << expense.amount << '\n';
    }

    cout << string(60, '-') << '\n';
    cout << "Total budgeted expenses: " << fixed << setprecision(2) << totalExpenses() << '\n';
    cout << "Disposable income:       " << fixed << setprecision(2) << disposableIncome(netWorth) << '\n';
}
