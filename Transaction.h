#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

enum class TransactionType {
    Income,
    Expense,
    Transfer
};

struct Transaction {
    string date;
    string accountName;
    TransactionType type;
    string category;
    double amount;
    string description;
};

string typeToString(TransactionType type);
TransactionType stringToType(const string& value);

#endif
