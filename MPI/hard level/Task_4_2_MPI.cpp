#include <iostream>
#include <mpi.h>
#include <random>

int const n = 12;

void print(int*, int data, int length);

int main(int argc, char** argv) {

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int step = n / size + 1;
    int master_count = n % step;

    int* a = new int[n];
    int* v = new int[step];

    if (rank == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 100);

        for (int i = 0; i < n; i++) {
            a[i] = dist(gen);
            printf("%d ", a[i]);
        }
        printf("\n");

        int start = master_count;
        for (int i = 1; i < size; i++) {
            MPI_Send(a + start, step, MPI_INT, i, 77, MPI_COMM_WORLD);
            start += step;
        }

        printf("process %d: ", rank);
        print(a, 0, master_count);
        printf("\n");
    }
    else {
        v = new int[step];
        MPI_Recv(v, step, MPI_INT, 0, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("process %d: ", rank);
        if (rank < n / step + 1) {
            print(v, 0, step);
        }
        printf("\n");
    }

    MPI_Finalize();
}


void print(int* a, int start, int length) {
    for (int i = start; i < length; i++) {
        printf("%d ", a[i]);
    }
}