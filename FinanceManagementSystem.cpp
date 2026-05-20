#include "FinanceManagementSystem.h"

#include "Analytics.h"
#include "Utils.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

FinanceManagementSystem::FinanceManagementSystem() {
    loadData();
}

FinanceManagementSystem::~FinanceManagementSystem() {
    saveData();
}

Account* FinanceManagementSystem::selectAccount() {
    if (accounts.empty()) {
        cout << "No accounts available. Create an account first.\n";
        return nullptr;
    }

    listAccounts();
    int choice = readInt("Choose account number: ", 1, static_cast<int>(accounts.size()));
    return accounts[choice - 1].get();
}

void FinanceManagementSystem::recordTransaction(const string& accountName, TransactionType type,
                                                const string& category, double amount,
                                                const string& description) {
    transactions.push_back({today(), accountName, type, category, amount, description});
}

void FinanceManagementSystem::addAccount() {
    cout << "\nAccount Types\n1. Mpesa\n2. Bank\n3. PayPal\n";
    int type = readInt("Choose account type: ", 1, 3);
    string name = readLine("Enter account name: ");
    double balance = readMoney("Enter opening balance: ");

    for (const auto& account : accounts) {
        if (account->getName() == name) {
            cout << "An account with that name already exists.\n";
            return;
        }
    }

    if (type == 1) {
        accounts.push_back(make_unique<MpesaAccount>(name, balance));
    } else if (type == 2) {
        accounts.push_back(make_unique<BankAccount>(name, balance));
    } else {
        accounts.push_back(make_unique<PaypalAccount>(name, balance));
    }

    recordTransaction(name, TransactionType::Income, "Opening Balance", balance, "Initial account balance");
    cout << "Account added successfully.\n";
}

void FinanceManagementSystem::listAccounts() const {
    cout << "\nAccounts\n";
    if (accounts.empty()) {
        cout << "No accounts have been created yet.\n";
        return;
    }

    cout << left << setw(5) << "#"
         << setw(18) << "Type"
         << setw(22) << "Name"
         << "Balance\n";
    cout << string(58, '-') << '\n';

    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << left << setw(5) << (i + 1);
        accounts[i]->display();
    }
    cout << "Cumulative net worth: " << fixed << setprecision(2) << netWorth() << '\n';
}

double FinanceManagementSystem::netWorth() const {
    double total = 0;
    for (const auto& account : accounts) {
        total += account->getBalance();
    }
    return total;
}

void FinanceManagementSystem::deposit() {
    Account* account = selectAccount();
    if (account == nullptr) return;

    double amount = readMoney("Enter income amount: ");
    string category = readLine("Enter income category: ");
    string description = readLine("Enter description: ");
    account->deposit(amount);
    recordTransaction(account->getName(), TransactionType::Income, category, amount, description);
    cout << "Deposit recorded.\n";
}

void FinanceManagementSystem::withdraw() {
    Account* account = selectAccount();
    if (account == nullptr) return;

    double amount = readMoney("Enter expenditure amount: ");
    if (!account->withdraw(amount)) {
        cout << "Insufficient account balance.\n";
        return;
    }

    cout << "1. Recurring constant expense\n";
    cout << "2. Recurring fluctuating expense\n";
    cout << "3. Emergency expense\n";
    cout << "4. Other expense\n";
    int option = readInt("Choose expense category: ", 1, 4);

    string category;
    if (option == 1) category = "Recurring Constant";
    else if (option == 2) category = "Recurring Fluctuating";
    else if (option == 3) category = "Emergency";
    else category = readLine("Enter custom category: ");

    string description = readLine("Enter description: ");
    recordTransaction(account->getName(), TransactionType::Expense, category, amount, description);
    cout << "Expenditure recorded.\n";
}

void FinanceManagementSystem::transferFunds() {
    if (accounts.size() < 2) {
        cout << "Create at least two accounts before transferring funds.\n";
        return;
    }

    cout << "\nSource account\n";
    Account* source = selectAccount();
    if (source == nullptr) return;

    cout << "\nDestination account\n";
    Account* destination = selectAccount();
    if (destination == nullptr) return;

    if (source == destination) {
        cout << "Source and destination accounts must be different.\n";
        return;
    }

    double amount = readMoney("Enter transfer amount: ");
    if (!source->withdraw(amount)) {
        cout << "Insufficient source account balance.\n";
        return;
    }

    destination->deposit(amount);
    recordTransaction(source->getName(), TransactionType::Transfer, "Transfer Out", amount,
                      "To " + destination->getName());
    recordTransaction(destination->getName(), TransactionType::Transfer, "Transfer In", amount,
                      "From " + source->getName());
    cout << "Transfer completed.\n";
}

void FinanceManagementSystem::manageBudget() {
    string name = readLine("Enter expense name: ");
    cout << "1. Recurring constant expense\n";
    cout << "2. Recurring fluctuating expense\n";
    cout << "3. Emergency expense\n";
    int option = readInt("Choose budget category: ", 1, 3);
    double amount = readMoney("Enter expected amount: ");

    string category = option == 1 ? "Recurring Constant"
                      : option == 2 ? "Recurring Fluctuating"
                                    : "Emergency";
    budgetManager.addExpense(name, category, amount);
    cout << "Budget expense added.\n";
}

void FinanceManagementSystem::showBudget() const {
    budgetManager.display(netWorth());
}

void FinanceManagementSystem::addGoal() {
    string name = readLine("Enter goal or wishlist item: ");
    double target = readMoney("Enter target amount: ");
    double saved = readMoney("Enter amount already saved: ");
    goals.emplace_back(name, target, saved);
    cout << "Goal added.\n";
    if (goals.back().achieved()) {
        cout << "Notification: savings target already achieved.\n";
    }
}

void FinanceManagementSystem::updateGoal() {
    if (goals.empty()) {
        cout << "No goals available.\n";
        return;
    }

    listGoals();
    int choice = readInt("Choose goal number: ", 1, static_cast<int>(goals.size()));
    double amount = readMoney("Enter new savings amount to add: ");
    goals[choice - 1].addSavings(amount);

    if (goals[choice - 1].achieved()) {
        cout << "Notification: savings target achieved for " << goals[choice - 1].getName() << ".\n";
    } else {
        cout << "Goal progress updated.\n";
    }
}

void FinanceManagementSystem::listGoals() const {
    cout << "\nGoals and Wishlist\n";
    if (goals.empty()) {
        cout << "No goals have been created yet.\n";
        return;
    }

    cout << left << setw(5) << "#"
         << setw(25) << "Goal"
         << setw(14) << "Target"
         << setw(14) << "Saved"
         << setw(10) << "Progress"
         << "Status\n";
    cout << string(80, '-') << '\n';

    for (size_t i = 0; i < goals.size(); ++i) {
        cout << left << setw(5) << (i + 1);
        goals[i].display();
    }
}

void FinanceManagementSystem::showAnalytics() const {
    Analytics::showReport(transactions);
}

void FinanceManagementSystem::saveData() const {
    ofstream file(storageFile);
    if (!file) {
        cout << "Warning: could not save data.\n";
        return;
    }

    for (const auto& account : accounts) {
        file << "ACCOUNT|" << account->getType() << '|'
             << account->getName() << '|'
             << fixed << setprecision(2) << account->getBalance() << '\n';
    }

    for (const auto& expense : budgetManager.getExpenses()) {
        file << "BUDGET|" << expense.name << '|'
             << expense.category << '|'
             << fixed << setprecision(2) << expense.amount << '\n';
    }

    for (const auto& goal : goals) {
        file << "GOAL|" << goal.getName() << '|'
             << fixed << setprecision(2) << goal.getTargetAmount() << '|'
             << goal.getSavedAmount() << '\n';
    }

    for (const auto& transaction : transactions) {
        file << "TRANSACTION|" << transaction.date << '|'
             << transaction.accountName << '|'
             << typeToString(transaction.type) << '|'
             << transaction.category << '|'
             << fixed << setprecision(2) << transaction.amount << '|'
             << transaction.description << '\n';
    }
}

void FinanceManagementSystem::loadData() {
    ifstream file(storageFile);
    if (!file) {
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> parts;
        string part;
        stringstream parser(line);

        while (getline(parser, part, '|')) {
            parts.push_back(part);
        }

        if (parts.empty()) continue;

        if (parts[0] == "ACCOUNT" && parts.size() == 4) {
            string type = parts[1];
            string name = parts[2];
            double balance = stod(parts[3]);

            if (type == "Mpesa") {
                accounts.push_back(make_unique<MpesaAccount>(name, balance));
            } else if (type == "Bank") {
                accounts.push_back(make_unique<BankAccount>(name, balance));
            } else {
                accounts.push_back(make_unique<PaypalAccount>(name, balance));
            }
        } else if (parts[0] == "BUDGET" && parts.size() == 4) {
            budgetManager.addExpense(parts[1], parts[2], stod(parts[3]));
        } else if (parts[0] == "GOAL" && parts.size() == 4) {
            goals.emplace_back(parts[1], stod(parts[2]), stod(parts[3]));
        } else if (parts[0] == "TRANSACTION" && parts.size() == 7) {
            transactions.push_back({parts[1], parts[2], stringToType(parts[3]),
                                    parts[4], stod(parts[5]), parts[6]});
        }
    }
}

void FinanceManagementSystem::run() {
    int choice;
    do {
        cout << "\nFINANCE MANAGEMENT SYSTEM\n";
        cout << "1. Add financial account\n";
        cout << "2. View accounts and net worth\n";
        cout << "3. Record income/deposit\n";
        cout << "4. Record expenditure/withdrawal\n";
        cout << "5. Transfer funds between accounts\n";
        cout << "6. Add budget expense\n";
        cout << "7. View budget and disposable income\n";
        cout << "8. Add wishlist/financial goal\n";
        cout << "9. Update goal savings\n";
        cout << "10. View goals\n";
        cout << "11. View analytics and transaction history\n";
        cout << "0. Save and exit\n";

        choice = readInt("Choose an option: ", 0, 11);

        switch (choice) {
            case 1: addAccount(); break;
            case 2: listAccounts(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: transferFunds(); break;
            case 6: manageBudget(); break;
            case 7: showBudget(); break;
            case 8: addGoal(); break;
            case 9: updateGoal(); break;
            case 10: listGoals(); break;
            case 11: showAnalytics(); break;
            case 0:
                saveData();
                cout << "Data saved. Goodbye.\n";
                break;
        }
    } while (choice != 0);
}
