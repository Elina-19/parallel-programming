#include <iostream>
#include <mpi.h>
#include <random>
#include <chrono>

int const n = 100;

int* merge(int* l_buff, int* r_buff, int l_size, int r_size);
int* merge_sort(int* data, int left, int right);
void print(std::string, int* data, int length);


int main(int argc, char** argv) {
    int* v = new int[n];
    int* a = new int[1];

    std::chrono::high_resolution_clock::time_point start_t, end_t;

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int step = n / size;
    int master_count = step + n % size;

    // process 0: sends params to all processes
    if (rank == 0) {    

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 100);

        for (int i = 0; i < n; i++) {
            v[i] = dist(gen);
        }
        //print("array: ", v, n);

        start_t = std::chrono::high_resolution_clock::now();

        int start = master_count;
        for (int i = 1; i < size; i++) {
            MPI_Send(v + start, step, MPI_INT, i, 77, MPI_COMM_WORLD);
            start += step;
        }
    } else {
        a = new int[step];
        MPI_Recv(a, step, MPI_INT, 0, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // process 0: receives params from all processes
    if (rank == 0) {    

        int* sorted = merge_sort(v, 0, master_count - 1);

        int length = master_count;

        int* temp = new int[step];
        for (int i = 1; i < size; i++) {
            MPI_Recv(temp, step, MPI_INT, i, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            sorted = merge(sorted, temp, length, step);
            length += step;
        }

        end_t = std::chrono::high_resolution_clock::now();

        //print("sorted array: ", sorted, length);

        printf("Total time: %f\n", std::chrono::duration_cast<std::chrono::duration<float>>(end_t - start_t).count());
    }
    else {
        a = merge_sort(a, 0, step - 1);
        MPI_Send(a, step, MPI_INT, 0, 77, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

int* merge(int* l_buff, int* r_buff, int l_size, int r_size) {
    int width = l_size + r_size;
    int* target = new int[width];

    int l_cur = 0, r_cur = 0, i = 0;
    while (l_cur < l_size && r_cur < r_size) {
        if (l_buff[l_cur] < r_buff[r_cur]) {
            target[i++] = l_buff[l_cur++];
        }
        else {
            target[i++] = r_buff[r_cur++];
        }
    }
    while (l_cur < l_size) {
        target[i++] = l_buff[l_cur++];
    }

    while (r_cur < r_size) {
        target[i++] = r_buff[r_cur++];
    }

    return target;
}

int* merge_sort(int* data, int left, int right) {
    if (left == right) {
        int* temp = new int[1];
        temp[0] = data[left];
        return temp;
    }

    int middle = (left + right) / 2;

    int* l_buff = merge_sort(data, left, middle);
    int* r_buff = merge_sort(data, middle + 1, right);

    return merge(l_buff, r_buff, middle - left + 1, right - middle);
}

void print(std::string mess, int* data, int length) {
    std::cout << mess + "[";
    for (int i = 0; i < length - 1; i++) {
        printf("%d ", data[i]);
    }

    printf("%d]\n", data[length - 1]);
}
