#include <stdio.h>


// variables
const int PIN = 1234;
float balance = 1000.0;
const int MAX_ATTEMPTS = 3;

int login(void) {
    int input_pin;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter PIN: ");
        scanf("%d", &input_pin);

        if (input_pin == PIN) {
            printf("Login successful!\n");
            return 1;
        } else {
            attempts++;
            printf("Incorrect PIN. Attempts remaining: %d\n", MAX_ATTEMPTS - attempts);
        }
    }

    printf("Max attempts exceeded. Access denied.\n");
    return 0;
}

void checkBalance(void) {
    printf("Current balance: KES %.2f\n", balance);
}

void deposit(void) {
    float amount;
    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    if (amount > 0) {
        balance += amount;
        printf("Deposited KES %.2f. New balance: KES %.2f\n", amount, balance);
    } else {
        printf("Invalid amount. Must be positive.\n");
    }
}

void withdraw(void) {
    float amount;
    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= balance) {
        balance -= amount;
        printf("Withdrew KES %.2f. New balance: KES %.2f\n", amount, balance);
    } else if (amount <= 0) {
        printf("Invalid amount. Must be positive.\n");
    } else {
        printf("Insufficient balance.\n");
    }
}

void showMenu(void) {
    printf("\n=== ATM MENU ===\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Exit\n");
    printf("Choose option: ");
}

int main(void) {
    int choice;

    if (!login()) {
        return 1; // Exit if login fails
    }

    while (login) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                printf("Thank you for using ATM. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
