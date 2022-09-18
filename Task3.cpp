#include <iostream>
#include <omp.h>

int main()
{
	int a = 5;
	int b = 7;

	printf("Before 1 parallel area: a = %d, b = %d \n", a, b);

	#pragma omp parallel private(a) firstprivate(b) num_threads(2)
	{
		a = 5;
		int num = omp_get_thread_num();
		a += num;
		b += num;

		printf("In 1 parallel area : a = %d, b = %d \n", a, b);
	}

	printf("After 1 parallel area : a = %d, b = %d \n", a, b);

	printf("Before 2 parallel area: a = %d, b = %d \n", a, b);

	#pragma omp parallel num_threads(4) shared(a) private(b)
	{
		b = 7;
		int num = omp_get_thread_num();

		#pragma omp atomic
		a -= num;
		b -= num;

		printf("In 2 parallel area : a = %d, b = %d \n", a, b);
	}

	printf("After 2 parallel area : a = %d, b = %d", a, b);
}
