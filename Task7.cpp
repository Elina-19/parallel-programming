#include <omp.h>
#include <stdio.h>

int main() {

	int a[12], b[12], c[12];

	#pragma omp parallel for schedule(static, 3) num_threads(3)
	for (int i = 0; i < 12; i++) {
		a[i] = i;
		b[i] = i;
		printf("Thread %d of %d \n", omp_get_thread_num(), omp_get_num_threads());
	}

	for (int i = 0; i < 12; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", b[i]);
	}
	printf("\n");

	#pragma omp parallel for schedule(dynamic, 4) num_threads(4)
	for (int i = 0; i < 12; i++) {
		c[i] = a[i] + b[i];
		printf("Thread %d of %d \n", omp_get_thread_num(), omp_get_num_threads());
	}

	for (int i = 0; i < 12; i++) {
		printf("%d ", c[i]);
	}
}