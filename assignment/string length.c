#include <stdio.h>
#include <string.h>

int main() {
    char name[100];

    printf("Enter a string (e.g., your name): ");
    scanf("%s", name);  // Use fgets for full names with spaces


    printf("Length of the string: %lu\n", strlen(name));
    return 0;
}
