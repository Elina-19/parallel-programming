#include <iostream>

int main()
{
    int a[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 20};

    float average_a = 0;
    float average_b = 0;

    #pragma omp parallel for reduction(+:average_a) reduction(+:average_b)
    for (int i = 0; i < 10; i++) {
        average_a += a[i];
        average_b += b[i];
    }

    average_a = average_a / 10;
    average_b = average_b / 10;

    printf("Average of a = %f, average of b  = %f \n", average_a, average_b);

    char sign = '=';

    if (average_a > average_b) {
        sign = '>';
    }
    if (average_a < average_b) {
        sign = '<';
    }

    printf("%f %c %f", average_a, sign, average_b);
}