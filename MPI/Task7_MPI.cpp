#include <iostream>
#include <mpi.h>
#include <random>
#include <math.h>

int main(int argc, char** argv)
{
    int rank;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int count;

    const int SIZE = 15;
    const int PART = 5;


    if (rank == 0) {
        int x[SIZE];
        int y[SIZE];

        for (int i = 0; i < SIZE; ++i) {
            x[i] = dist(gen);
            y[i] = dist(gen);
        }

        printf("x: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", x[i]);
        }
        printf("\ny: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", y[i]);
        }
        printf("\n");

        int n = 1;
        for (int i = 0; i < SIZE; i += PART, n++) {
            MPI_Send(&x[i], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            MPI_Send(&y[i], PART, MPI_INT, n, 11, MPI_COMM_WORLD);
        }

        n = 1;
        for (int i = 0; i < SIZE; i += PART, n++) {
            MPI_Recv(&x[i], PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            MPI_Recv(&y[i], PART, MPI_INT, n, 11, MPI_COMM_WORLD, &status);
        }

        printf("x: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", x[i]);
        }
        printf("\ny: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", y[i]);
        }
    }
    else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int x[PART];
        int y[PART];

        MPI_Recv(&x[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&y[0], count, MPI_INT, 0, 11, MPI_COMM_WORLD, &status);

        MPI_Send(&y, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
        MPI_Send(&x, count, MPI_INT, 0, 11, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}