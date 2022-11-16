#include <iostream>
#include <mpi.h>
#include <random>

void main(int argc, char** argv) {

    int rank, word_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &word_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    int const block = 10;
    int const n = 120;
    int x[n], y[block];

    if (rank == 0) {
        printf("x: ");
        for (int i = 0; i < n; i++) {
            x[i] = dist(gen);
            printf("%d ", x[i]);
        }
        printf("\n\n\n||x||: ");
    }

    MPI_Scatter(&x[0], block, MPI_INT, &y[0], block, MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
    for (int i = 0; i < block; ++i) {
        sum += abs(y[i]);
    }

    int res;
    MPI_Reduce(&sum, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("%d", res);
    }
    printf("\n");

    finish: MPI_Finalize();
}