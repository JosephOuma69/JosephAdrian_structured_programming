#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "Transaction.h"

#include <vector>

using namespace std;

class Analytics {
public:
    static void showReport(const vector<Transaction>& transactions);
};

#endif
