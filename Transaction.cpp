#include "Transaction.h"

using namespace std;

string typeToString(TransactionType type) {
    switch (type) {
        case TransactionType::Income:
            return "Income";
        case TransactionType::Expense:
            return "Expense";
        case TransactionType::Transfer:
            return "Transfer";
    }
    return "Unknown";
}

TransactionType stringToType(const string& value) {
    if (value == "Income") return TransactionType::Income;
    if (value == "Transfer") return TransactionType::Transfer;
    return TransactionType::Expense;
}
