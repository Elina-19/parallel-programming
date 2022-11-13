#include <iostream>
#include <omp.h>
#include <string>

int main()
{
    #pragma omp parallel num_threads(8)
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        std::string str = "Hello world " + std::to_string(thread_id) + " of " + std::to_string(nthread) + " \n";
        std::cout << str;
    }
}
