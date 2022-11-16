#include <mpi.h>
#include <iostream>
#include <random>

const int N = 8;
const int M = 6;
const int block = 12;

void main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a_block[block], b_block[block];

    if (rank == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 100);

        int a[N][M], b[N][M];

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                a[i][j] = dist(gen);
                b[i][j] = dist(gen);
            }
        }

        printf("A:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("B:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }

        MPI_Scatter(&(a[0][0]), block, MPI_INT, &a_block[0], block, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(&(b[0][0]), block, MPI_INT, &b_block[0], block, MPI_INT, 0, MPI_COMM_WORLD);

        for (int i = 0; i < block; ++i) {
            a_block[i] *= b_block[i];
        }

        MPI_Gather(&a_block[0], block, MPI_INT, &(a[0][0]), block, MPI_INT, 0, MPI_COMM_WORLD);

        printf("C:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
    else {
        int temp;

        MPI_Scatter(&temp, block, MPI_INT, &a_block[0], block, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(&temp, block, MPI_INT, &b_block[0], block, MPI_INT, 0, MPI_COMM_WORLD);

        for (int i = 0; i < block; ++i) {
            a_block[i] *= b_block[i];
        }

        MPI_Gather(&a_block[0], block, MPI_INT, &temp, block, MPI_INT, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
}