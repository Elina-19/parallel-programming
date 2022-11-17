#include <iostream>
#include <mpi.h>
#include <random>
#include <chrono>

int const n = 30000;

void ping_pong_2(int rank);
void ping_pong_1(int rank);

int main(int argc, char** argv) {

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    ping_pong_2(rank);
    //ping_pong_1(rank);

    MPI_Finalize();
}

void ping_pong_2(int rank) {
    static int* mess = new int[n];

    if (rank == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 100);

        for (int i = 0; i < n; i++) {
            mess[i] = dist(gen);
        }

        auto start = std::chrono::high_resolution_clock::now();

        MPI_Send(mess, n, MPI_INT, 1, 77, MPI_COMM_WORLD);
        MPI_Recv(mess, n, MPI_INT, 1, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        auto end = std::chrono::high_resolution_clock::now();

        float time_took = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
        printf("Time consistent %f \n", time_took);
    }
    else {
        int* received = new int[n];

        MPI_Recv(received, n, MPI_INT, 0, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(received, n, MPI_INT, 0, 77, MPI_COMM_WORLD);
    }
}


void ping_pong_1(int rank) {
    static int* mess = new int[n];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    for (int i = 0; i < n; i++) {
        mess[i] = dist(gen);
    }

    std::chrono::high_resolution_clock::time_point start;

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        start = std::chrono::high_resolution_clock::now();

        MPI_Send(mess, n, MPI_INT, 1, 77, MPI_COMM_WORLD);
    }
    else {
        start = std::chrono::high_resolution_clock::now();

        MPI_Send(mess, n, MPI_INT, 0, 77, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        static int* received = new int[n];

        MPI_Recv(received, n, MPI_INT, 1, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else {
        static int* mess2 = new int[n];

        MPI_Recv(mess2, n, MPI_INT, 0, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    auto end = std::chrono::high_resolution_clock::now();

    float time_took = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    printf("Time consistent %f \n", time_took);
}