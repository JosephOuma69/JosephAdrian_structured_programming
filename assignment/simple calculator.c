#include <stdio.h>

int main() {
    float num1, num2, result;
    char op;

    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%f", &num2);

    if (op == '+') {
        result = num1 + num2;
        printf("Result: %.2f\n", result);
    }

    if (op == '-') {
        result = num1 - num2;
        printf("Result: %.2f\n", result);
    }

    if (op == '*') {
        result = num1 * num2;
        printf("Result: %.2f\n", result);
    }

    if (op == '/') {
        if (num2 == 0) {
            printf("Error: Division by zero\n");
        } else {
            result = num1 / num2;
            printf("Result: %.2f\n", result);
        }
    }

    return 0;
}
