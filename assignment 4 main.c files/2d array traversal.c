#include <stdio.h>

int main() {
    // Declare and initialize a 6x4 2D array
    int arr[6][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
        {17, 18, 19, 20},
        {21, 22, 23, 24}
    };

    // Traverse and print each element
    printf("2D Array Traversal:\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            printf("Element at [%d][%d] = %d\n", i, j, arr[i][j]);
        }
    }

    return 0;
}
