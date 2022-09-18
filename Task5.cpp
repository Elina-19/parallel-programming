#include <random>
#include <iostream>
#include <omp.h>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    int d[6][8];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = dist(gen);
            std::cout << d[i][j] << " ";
        }
    }
    std::cout << "\n";

    #pragma omp parallel sections
    {
        #pragma omp section 
        {
            float average = 0.0;
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 8; j++) {
                    average += d[i][j];
                }
            }
            average = average/(6*8);

            printf("Thread %d, average = %f \n", omp_get_thread_num(), floor(average*100)/100);
        }

        #pragma omp section
        {
            int min = d[0][0];
            int max = d[0][0];
            for (int i = 0; i < 6; ++i) {
                for (int j = 1; j < 8; j++) {
                    if (d[i][j] < min) {
                        min = d[i][j];
                    }

                    if (d[i][j] > max) {
                        max = d[i][j];
                    }
                }
            }

            printf("Thread %d, min = %d, max = %d \n", omp_get_thread_num(), min, max);
        }

        #pragma omp section
        {
            int count = 0;
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] % 3 == 0) {
                        count++;
                    }
                }
            }

            printf("Thread %d, count the numbers are multiples of 3 = %d \n", omp_get_thread_num(), count);
        }
    }
}