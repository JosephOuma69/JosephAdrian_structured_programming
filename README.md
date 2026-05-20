# Finance Management System

This is a modular C++ Object-Oriented Programming console project.

## How to run in Visual Studio

Open `FinanceManagementSystem.sln`, then press `Ctrl + F5` to run without debugging.

## Manual g++ command

```bash
g++ -std=c++17 main.cpp Account.cpp Analytics.cpp BudgetManager.cpp FinanceManagementSystem.cpp Goal.cpp Transaction.cpp Utils.cpp -o finance_system
```

## Main modules

- `main.cpp` - program entry point
- `Account.h` / `Account.cpp` - account classes
- `BudgetManager.h` / `BudgetManager.cpp` - budgets and disposable income
- `Goal.h` / `Goal.cpp` - wishlist and savings goals
- `Analytics.h` / `Analytics.cpp` - reports and transaction history
- `Transaction.h` / `Transaction.cpp` - transaction model
- `Utils.h` / `Utils.cpp` - input, date, and helper functions
- `FinanceManagementSystem.h` / `FinanceManagementSystem.cpp` - main controller
