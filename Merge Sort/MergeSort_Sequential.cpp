#include <iostream>
#include <vector>
#include <chrono>
#include <random>

int* merge(int* l_buff, int* r_buff, int l_size, int r_size);
int* merge_sort(int* data, int left, int right);
void print(std::string mess, int* data, int length);

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 200);

    int* vect;
    int* vect2;

    std::vector<int> sizes = {200, 300};

    /*std::vector<int> sizes = {100, 300, 500, 700, 1000,
    10000, 15000, 20000, 25000, 30000, 50000,
    100000, 20000, 300000, 400000, 500000, 600000,
    1000000, 2000000, 3000000};*/

    //for (int s = 0; s < 20; s++) {
    for (int s = 0; s < 2; s++) {

        vect = new int[sizes[s]];
        for (int i = 0; i < sizes[s]; i++) {
            vect[i] = dist(gen);
        }
        //print("array: ", vect, sizes[s]);

        float result = 0;
        for (int i = 0; i < 1; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            vect2 = merge_sort(vect, 0, sizes[s] - 1);
            auto end = std::chrono::high_resolution_clock::now();
            float time_took = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

            result += time_took;
        }
        //print("sorted array: ", vect2, sizes[s]);

        printf("Array size: %d, time consistent %f \n", sizes[s], result / 1);
    }
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
