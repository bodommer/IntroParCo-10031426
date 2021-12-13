#define _GNU_SOURCE

#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[]) {

	MPI_Init(&argc, &argv);

        printf("Hello, world!\n");

	MPI_Finalize();

	return 0;
}
