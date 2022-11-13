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

    const int LENGTH = 8;
    const int HEIGHT = 8;
    const int PART = 8;

    if (rank == 0) {
        int a[HEIGHT][LENGTH];
        int t_a[LENGTH][HEIGHT];

        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < LENGTH; j++) {
                a[i][j] = dist(gen);
            }
        }

        printf("A: \n");
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < LENGTH; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        int n = 1;
        for (int i = 0; i < HEIGHT; i += PART) {
            for (int j = 0; j < LENGTH; j += PART, n++) {
                MPI_Send(&a[i][j], PART*PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            }
        }

        n = 1;
        for (int i = 0; i < HEIGHT; i += PART) {
            for (int j = 0; j < LENGTH; j += PART, n++) {
                MPI_Recv(&t_a[i][j], PART*PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            }
        }

        printf("C: \n");
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                printf("%d ", t_a[i][j]);
            }
            printf("\n");
        }
    }
    else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[PART][PART];
        int t_a[PART][PART];

        MPI_Recv(&a[0][0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < PART; j++) {
                t_a[j][i] = a[i][j];
            }
        }

        MPI_Send(&t_a, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

