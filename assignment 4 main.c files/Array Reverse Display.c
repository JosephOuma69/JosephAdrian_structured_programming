#include <stdio.h>

int main() {
    int n;

    // Ask for the number of elements
    printf("Input the number of elements to store in the array: ");
    scanf("%d", &n);

    int arr[n];

    // Read elements into the array
    printf("Input %d number of elements in the array:\n", n);
    for (int i = 0; i < n; i++) {
        printf("element - %d : ", i);
        scanf("%d", &arr[i]);
    }

    // Display the original array
    printf("The values store into the array are : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // Display the array in reverse
    printf("\nThe values store into the array in reverse are : ");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }

    return 0;
}
