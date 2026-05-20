#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

string today();
string sanitize(const string& value);
double readMoney(const string& prompt);
int readInt(const string& prompt, int minimum, int maximum);
string readLine(const string& prompt);

#endif
