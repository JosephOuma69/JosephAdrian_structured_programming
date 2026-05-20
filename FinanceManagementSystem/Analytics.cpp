#include "Analytics.h"

#include <iomanip>
#include <iostream>

using namespace std;

void Analytics::showReport(const vector<Transaction>& transactions) {
    double income = 0;
    double expenses = 0;
    double transfers = 0;

    for (const auto& transaction : transactions) {
        if (transaction.type == TransactionType::Income) {
            income += transaction.amount;
        } else if (transaction.type == TransactionType::Expense) {
            expenses += transaction.amount;
        } else {
            transfers += transaction.amount;
        }
    }

    cout << "\nFinancial Analytics\n";
    cout << "Total income:       " << fixed << setprecision(2) << income << '\n';
    cout << "Total expenditure:  " << fixed << setprecision(2) << expenses << '\n';
    cout << "Total transfers:    " << fixed << setprecision(2) << transfers << '\n';
    cout << "Net movement:       " << fixed << setprecision(2) << (income - expenses) << '\n';

    cout << "\nTransaction History\n";
    cout << left << setw(13) << "Date"
         << setw(18) << "Account"
         << setw(12) << "Type"
         << setw(22) << "Category"
         << setw(12) << "Amount"
         << "Description\n";
    cout << string(95, '-') << '\n';

    for (const auto& transaction : transactions) {
        cout << left << setw(13) << transaction.date
             << setw(18) << transaction.accountName
             << setw(12) << typeToString(transaction.type)
             << setw(22) << transaction.category
             << setw(12) << fixed << setprecision(2) << transaction.amount
             << transaction.description << '\n';
    }
}
