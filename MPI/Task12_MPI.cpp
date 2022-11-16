#include <iostream>
#include <mpi.h>
#include <random>

int const N = 12;

void main(int argc, char **argv) {
 
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int const block = 3;

    int x[N], x_block[block], y[N], y_block[N];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);
 
    if (rank == 0) {
        for (int i = 0; i < N; ++i) {
            x[i] = dist(gen);
            y[i] = dist(gen);
        }
    }

    MPI_Scatter(&x[0], block, MPI_INT, &x_block[0], block, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&y[0], block, MPI_INT, &y_block[0], block, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("x : ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", x[i]);
        }

        printf("\ny : ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", y[i]);
        }
        printf("\n");
    }

    int sum = 0;
    for (int i = 0; i < block; ++i) { 
        sum += x_block[i] * y_block[i];
    }
 
    int result;

    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("result = %d", result);
    }

    MPI_Finalize();
}
