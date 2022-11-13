#include <iostream>
#include <math.h>

int main() {

    int a[30] {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    int res = 0;

    #pragma omp parallel for reduction(+:res)
    for (int i = 0; i < 30; i++) {
        if (a[i] == 1) {
            res += pow(2, 29 - i);
        }
    }

    printf("Result = %d", res);
}