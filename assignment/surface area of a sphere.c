#include <stdio.h>
#define PI 3.14159

int main() {
    float radius, surfaceArea;

    printf("Enter the radius of the sphere: ");
    scanf("%f", &radius);

    surfaceArea = 4 * PI * radius * radius;
    printf("Surface Area: %.2f\n", surfaceArea);

    return 0;
}