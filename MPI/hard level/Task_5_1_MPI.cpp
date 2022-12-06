#include <mpi.h>
#include <iostream>
#include <random>

const int N = 8;

void main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Datatype type;
        MPI_Datatype row;

        MPI_Type_contiguous(8, MPI_INT, &row);
        MPI_Type_commit(&row);
        MPI_Type_vector(4, 1, 2, row, &type);
        MPI_Type_commit(&type);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 100);

        int a[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = dist(gen);
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        MPI_Send(&(a[0][0]), 1, type, 1, 123, MPI_COMM_WORLD);
        MPI_Send(&(a[1][0]), 1, type, 2, 123, MPI_COMM_WORLD);
    }
    else if (rank % 2 == 1) {

        int b[4][8];
        MPI_Recv(&(b[0][0]), 4 * 8, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Нечётные: \n");
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    else {
        int c[4][8];
        MPI_Recv(&(c[0][0]), 4 * 8, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Чётные: \n");
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    MPI_Finalize();
}