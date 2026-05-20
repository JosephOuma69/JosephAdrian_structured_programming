#include "Goal.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>

using namespace std;

Goal::Goal(string goalName, double target, double saved)
    : name(move(goalName)), targetAmount(target), savedAmount(saved) {}

string Goal::getName() const {
    return name;
}

double Goal::getTargetAmount() const {
    return targetAmount;
}

double Goal::getSavedAmount() const {
    return savedAmount;
}

bool Goal::achieved() const {
    return savedAmount >= targetAmount;
}

double Goal::progressPercent() const {
    if (targetAmount == 0) return 100;
    return min(100.0, (savedAmount / targetAmount) * 100.0);
}

void Goal::addSavings(double amount) {
    savedAmount += amount;
}

void Goal::display() const {
    cout << left << setw(25) << name
         << setw(14) << fixed << setprecision(2) << targetAmount
         << setw(14) << savedAmount
         << setw(10) << progressPercent() << "%";
    if (achieved()) {
        cout << "  Target achieved";
    }
    cout << '\n';
}
