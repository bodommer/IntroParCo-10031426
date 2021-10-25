#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
	int nthreads = 0;
	int tid = 0;
	printf("Entering parallel region\n");
	#pragma omp parallel private(nthreads, tid)
	{
		tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		if (tid == 0) {
			fprintf(stdout, "Computing XXX using %d threads per \n", nthreads);
		}
		fprintf(stdout, "Hello, I am thread #%d\n", tid);
	}
	printf("Leaving parallel region\n");
}
