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

    const int LENGTH_B = 4;
    const int HEIGHT_A = 2;
    const int GENERAL = 5;
    const int PART = 5;

    if (rank == 0) {
        int a[HEIGHT_A][GENERAL];
        int b[GENERAL][LENGTH_B];
        int t_b[LENGTH_B][GENERAL];
        int c[HEIGHT_A][LENGTH_B];

        for (int i = 0; i < HEIGHT_A; ++i) {
            for (int j = 0; j < GENERAL; j++) {
                a[i][j] = dist(gen);
            }
        }

        for (int i = 0; i < GENERAL; ++i) {
            for (int j = 0; j < LENGTH_B; j++) {
                b[i][j] = 2;
                t_b[j][i] = 2;
            }
        }

        printf("A: \n");
        for (int i = 0; i < HEIGHT_A; ++i) {
            for (int j = 0; j < GENERAL; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\nB: \n");
        for (int i = 0; i < GENERAL; ++i) {
            for (int j = 0; j < LENGTH_B; j++) {
                printf("%d ", b[j][i]);
            }
            printf("\n");
        }
        printf("\n\n");

        int n = 1;
        for (int i = 0; i < HEIGHT_A; i++) {
            for (int j = 0; j < LENGTH_B; j++, n++) {
                MPI_Send(&a[i][0], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
                MPI_Send(&t_b[j][0], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            }
        }

        n = 1;
        for (int i = 0; i < HEIGHT_A; i++) {
            for (int j = 0; j < LENGTH_B; j++, n++) {
                MPI_Recv(&c[i][j], 1, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            }
        }

        printf("C: \n");
        for (int i = 0; i < HEIGHT_A; i++) {
            for (int j = 0; j < LENGTH_B; j++) {
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
        int c = 0;

        MPI_Recv(&a[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&b[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < count; ++i) {
            c += a[i] * b[i];
        }

        MPI_Send(&c, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
