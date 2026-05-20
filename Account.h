#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account {
private:
    string accountName;
    double balance;

public:
    Account(string name, double openingBalance);
    virtual ~Account() = default;

    string getName() const;
    double getBalance() const;
    virtual string getType() const = 0;
    virtual void display() const;
    void deposit(double amount);
    bool withdraw(double amount);
};

class MpesaAccount : public Account {
public:
    MpesaAccount(const string& name, double openingBalance);
    string getType() const override;
};

class BankAccount : public Account {
public:
    BankAccount(const string& name, double openingBalance);
    string getType() const override;
};

class PaypalAccount : public Account {
public:
    PaypalAccount(const string& name, double openingBalance);
    string getType() const override;
};

#endif
