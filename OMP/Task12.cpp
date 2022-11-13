#include <iostream>
#include <omp.h>
#include <string>

int main()
{
	#pragma omp parallel num_threads(8)
	{
		for (int i = 7; i >= 0; i--){
			#pragma omp barrier
			if (i == omp_get_thread_num()){
				printf("Hello world %d of %d \n", omp_get_thread_num(), omp_get_num_threads());
			}
		}
	}
}
