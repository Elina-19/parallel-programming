#include <mpi.h>
#include <iostream>
#include <random>

const int process = 5;
const int N = 15;

int main(int argc, char** argv)
{
	MPI_Comm comm;

	int* ranks = new int[]{1, 3, 6, 8, 9};
	int rank, size;
	int a[N];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Group wgroup, group1, group2;
	MPI_Comm_group(MPI_COMM_WORLD, &wgroup);
	MPI_Group_incl(wgroup, process, ranks, &group1);
	MPI_Group_excl(wgroup, process, ranks, &group2);

	MPI_Comm comm1, comm2;
	MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
	MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);

	if (comm1 != MPI_COMM_NULL) {
		MPI_Comm_rank(comm1, &rank);
	}
	if (comm2 != MPI_COMM_NULL) {
		MPI_Comm_rank(comm2, &rank);
	}

	if (comm1 != MPI_COMM_NULL && rank == 0) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 100);

		printf("init array: ");
		for (int i = 0; i < N; i++) {
			a[i] = dist(gen);
			printf("%d ", a[i]);
		}
		printf("\n");
	}

	if (comm1 != MPI_COMM_NULL) {
		MPI_Bcast(&a[0], N, MPI_INT, 0, comm1);

		printf("process: %d\n", rank);
		for (int i = 0; i < N; i++) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}

	if (comm1 != MPI_COMM_NULL && rank == process - 1) {
		MPI_Send(&a[0], N, MPI_INT, 0, 1, comm1);
	}

	if (comm1 != MPI_COMM_NULL && rank == 0) {
		int b[N];

		MPI_Recv(&b[0], N, MPI_INT, process - 1, 1, comm1, MPI_STATUSES_IGNORE);

		printf("received array:\n");
		for (int i = 0; i < N; i++) {
			printf("%d ", b[i]);
		}
	}

	if (comm1 != MPI_COMM_NULL) {
		MPI_Comm_free(&comm1);
	}
	if (comm2 != MPI_COMM_NULL) {
		MPI_Comm_free(&comm2);
	}

	MPI_Group_free(&group1);
	MPI_Group_free(&group2);

	MPI_Finalize();
}