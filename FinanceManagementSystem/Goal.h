#ifndef GOAL_H
#define GOAL_H

#include <string>

using namespace std;

class Goal {
private:
    string name;
    double targetAmount;
    double savedAmount;

public:
    Goal(string goalName, double target, double saved);
    string getName() const;
    double getTargetAmount() const;
    double getSavedAmount() const;
    bool achieved() const;
    double progressPercent() const;
    void addSavings(double amount);
    void display() const;
};

#endif
