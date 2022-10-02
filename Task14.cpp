#include <iostream>

int main() {

    int res = 0;

    #pragma omp parallel for reduction(+:res)
    for (int i = 0; i < 210; i++) {
        res += 2*i + 1;
    }

    printf("Result = %d", res);
}