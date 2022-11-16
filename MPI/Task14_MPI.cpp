#include <mpi.h>
#include <iostream>
#include <random>

const int n = 12;
const int m = 10;
const int block = 3;

void main(int argc, char** argv) {

    int A[n][m];

    int result;
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 100);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                A[i][j] = dist(gen);
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    int a[block][m];

    MPI_Scatter(&A[rank * block][0], block * m, MPI_INT, &a[0][0], block * m, MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
    int max = INT_MIN;
    for (int i = 0; i < block; i++) {
        for (int j = 0; j < m; j++) {
            sum += a[i][j];
        }
        if (sum > max) {
            max = sum;
        }
    }

    MPI_Reduce(&max, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result: %d", result);
    }

    MPI_Finalize();
}