#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-5, 100);

    int min, max;

    int d[6][8];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = dist(gen);
            std::cout << d[i][j] << " ";
        }
    }
    printf("\n");

    min = d[0][0];
    max = d[0][0];
    
    #pragma omp parallel for
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            if (d[i][j] > max) {
                #pragma omp critical
                max = d[i][j];
            }

            if (d[i][j] < min) {
                #pragma omp critical
                min = d[i][j];
            }
        }
    }

    printf("min = %d, max = %d", min, max);
}
