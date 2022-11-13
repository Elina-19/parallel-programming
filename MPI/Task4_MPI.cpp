#include <iostream>
#include <mpi.h>
#include <random>

int main(int argc, char** argv)
{
    int rank, count;

    const int LENGTH = 10;
    int a[LENGTH];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 1) {
        for (int i = 0; i < 10; ++i) {
            a[i] = dist(gen);
        }

        MPI_Send(&a, 10, MPI_INT, 0, 1, MPI_COMM_WORLD);
        MPI_Send(&a, 10, MPI_INT, 2, 1, MPI_COMM_WORLD);
        MPI_Send(&a, 10, MPI_INT, 3, 1, MPI_COMM_WORLD);
    } else {
        MPI_Probe(1, 1, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        MPI_Recv(&a, count, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
 
        for (int i = 0; i < 10; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
}
