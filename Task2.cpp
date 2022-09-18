#include <iostream>
#include <omp.h>

int main()
{
    int num_of_threads = 3;

    omp_set_num_threads(num_of_threads);
    #pragma omp parallel if (omp_get_max_threads() > 1)
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        printf("First parallel area: thread %d of %d \n", thread_id, nthread);
    }

    num_of_threads = 1;

    omp_set_num_threads(num_of_threads);
    #pragma omp parallel if (omp_get_max_threads() > 1)
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        printf("Second parallel area: thread %d of %d \n", thread_id, nthread);
    }
}