
#include <stdio.h>

int main() {
    int n, pos, value;

    // Ask for the size of the array
    printf("Input the size of array: ");
    scanf("%d", &n);

    int arr[n + 1]

    // Read elements into the array
    printf("Input %d elements in the array:\n", n);
    for (int i = 0; i < n; i++) {
        printf("element - %d : ", i);
        scanf("%d", &arr[i]);
    }

    // Display current list
    printf("The current list of the array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // Read value and position for insertion
    printf("\nInput the value to be inserted: ");
    scanf("%d", &value);
    printf("Input the Position, where the value to be inserted: ");
    scanf("%d", &pos);

    // Shift elements to the right
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert the value
    arr[pos] = value;
    n++;

    // Display new list
    printf("After Insert the element the new list is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
