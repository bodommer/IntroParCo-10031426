#define _GNU_SOURCE

#include <stdio.h>
#include "mpi.h"
#include <utmpx.h>

int main(int argc, char* argv[]) {

	int rank, size;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("I am %d running on core %d.\n", rank, sched_getcpu());

	MPI_Finalize();

	return 0;
}
