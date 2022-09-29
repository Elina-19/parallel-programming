#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    int a[30];
    for (int i = 0; i < 30; i++) {
        a[i] = dist(gen);
        std::cout << a[i] << " ";
    }
    printf("\n");

    int count = 0;

    #pragma omp parallel for
    for (int i = 0; i < 30; i++) {
        if (a[i] % 9 == 0) {
            #pragma omp atomic
            count++;
        }
    }

    printf("Result = %d", count);
}