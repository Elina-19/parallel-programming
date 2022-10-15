#include <iostream>
#include "mpi.h"

int main(int argc, char** argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Number of process: %d, size: %d\n", rank, size);

    MPI_Finalize();
}
