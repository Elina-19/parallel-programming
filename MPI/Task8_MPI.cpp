#include <iostream>
#include <mpi.h>
#include <random>

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

    const int LENGTH = 5;
    const int HEIGHT = 5; 
    const int PART = 5;

    if (rank == 0) {
        int a[LENGTH][HEIGHT];
        int b[LENGTH][HEIGHT];
        int c[LENGTH][HEIGHT];

        for (int i = 0; i < LENGTH; ++i) {
            for (int j = 0; j < HEIGHT; j++) {
                a[i][j] = dist(gen);
                b[i][j] = 2;
            }
        }

        printf("A: \n");
        for (int i = 0; i < LENGTH; ++i) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\nB: \n");
        for (int i = 0; i < LENGTH; ++i) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");

        int n = 1;
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < HEIGHT; j += PART, n++) {
                MPI_Send(&a[i][j], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
                MPI_Send(&b[i][j], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            }
        }

        n = 1;
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < HEIGHT; j += PART, n++) {
                MPI_Recv(&c[i][j], PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            }
        }

        printf("C: \n");
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }
    else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[PART];
        int b[PART];
        int c[PART];

        MPI_Recv(&a[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&b[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < count; ++i) {
            c[i] = a[i] * b[i];
        }
        MPI_Send(&c, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}