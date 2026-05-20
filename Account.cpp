#include "Account.h"

#include <iomanip>
#include <iostream>
#include <utility>

using namespace std;

Account::Account(string name, double openingBalance)
    : accountName(move(name)), balance(openingBalance) {}

string Account::getName() const {
    return accountName;
}

double Account::getBalance() const {
    return balance;
}

void Account::display() const {
    cout << left << setw(18) << getType()
         << setw(22) << accountName
         << fixed << setprecision(2) << balance << '\n';
}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount > balance) {
        return false;
    }
    balance -= amount;
    return true;
}

MpesaAccount::MpesaAccount(const string& name, double openingBalance)
    : Account(name, openingBalance) {}

string MpesaAccount::getType() const {
    return "Mpesa";
}

BankAccount::BankAccount(const string& name, double openingBalance)
    : Account(name, openingBalance) {}

string BankAccount::getType() const {
    return "Bank";
}

PaypalAccount::PaypalAccount(const string& name, double openingBalance)
    : Account(name, openingBalance) {}

string PaypalAccount::getType() const {
    return "PayPal";
}
