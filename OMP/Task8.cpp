#include <iostream>
#include <chrono>
#include <windows.h>

int main()
{
    int const rows = 10000, columns = 5000;

    int static matrix[rows][columns];
    int static vector[columns];
    int static result[rows];

    //matrix initialization
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = i + j;
            //printf("%d ", matrix[i][j]);
        }
        //printf("\n");
    }
    //printf("\n");

    //vector initialization
    for (int i = 0; i < columns; i++) {
        vector[i] = i;
        //printf("%d ", vector[i]);
    }
    //printf("\n");

    auto start = std::chrono::high_resolution_clock::now();
    //multiplication
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < columns; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
        //printf("%d ", result[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    //printf("\n");

    float time_took = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    printf("Time consistent %f \n", time_took);


    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < columns; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
        //printf("%d ", result[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    //printf("\n");

    time_took = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    printf("Time parallel %f", time_took);
}