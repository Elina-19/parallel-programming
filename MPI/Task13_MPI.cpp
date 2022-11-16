#include <mpi.h>
#include <iostream>
#include <random>

const int M = 10;
const int N = 12;

const int block = 3;

void main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x[M];

    int a_block[block][M];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    if (rank == 0) {
        for (int i = 0; i < M; ++i) {
            x[i] = dist(gen);
        }

        int a[N][M];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                a[i][j] = dist(gen);
            }
        }
        printf("A: \n");

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("x : ");
        for (int i = 0; i < M; ++i) {
            printf("%d ", x[i]);
        }
        printf("\n");
        
        MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(&(a[0][0]), block * M, MPI_INT, &(a_block[0][0]), block * M, MPI_INT, 0, MPI_COMM_WORLD);

    }
    else {
        MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);
        int result;
        MPI_Scatter(&result, block * M, MPI_INT, &(a_block[0][0]), block * M, MPI_INT, 0, MPI_COMM_WORLD);
    }

    int res[block];
    for (int i = 0; i < block; ++i) {
        res[i] = 0;
        for (int j = 0; j < M; ++j) {
            res[i] += a_block[i][j] * x[j];
        }
    }

    if (rank == 0) {
        int result[N];
        MPI_Gather(&res[0], block, MPI_INT, &result[0], block, MPI_INT, 0, MPI_COMM_WORLD);

        for (int i = 0; i < N; ++i) {
            printf("%d ", result[i]);
        }
    }
    else {
        int result;
        MPI_Gather(&res[0], block, MPI_INT, &result, block, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}