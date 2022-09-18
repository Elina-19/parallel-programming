#include <iostream>
#include <omp.h>

int main()
{
    int a[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int len = *(&a + 1) - a;
    int min;
    int max;

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section master
        {
            min = a[0];
            for (int i = 1; i < len; i++) {
                if (a[i] < min) {
                    min = a[i];
                }
            }
        }

        #pragma omp section
        {
            max = b[0];
            for (int i = 1; i < len; i++) {
                if (b[i] > max) {
                    max = b[i];
                }
            }
        }
    }

    printf("Min: %d, max: %d", min, max);
}