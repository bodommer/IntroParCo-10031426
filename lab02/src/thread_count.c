#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	int nthreads = -1;

	#pragma omp parallel shared(nthreads)
	{
		#pragma omp single
		{
			nthreads = omp_get_num_threads();
		}
	}

	
	int* thread_ids = malloc(nthreads * sizeof(int));
	
	static int id;

	#pragma omp threadprivate(id)

	printf("Entering parallel region\n");
	#pragma omp parallel shared(nthreads)
	{
		//#pragma omp section {
		id = omp_get_thread_num();
		thread_ids[id] = id;
		nthreads = omp_get_num_threads();
		fprintf(stdout, "Computing XXX using %d threads per \n", nthreads);
		//}
	}

	int result = nthreads;
	for (int i=0; i < nthreads; i++) {
		result -= i;
	}
	fprintf(stdout, "Expected result: %d\n", result);

	#pragma omp parallel
	{
		#pragma omp critical
		nthreads -= id;
	}

	#pragma omp parallel 
	{
		if (id == 0) {
			fprintf(stdout, "Computing XXX using %d threads per \n", nthreads);
		}
		fprintf(stdout, "Hello, I am thread #%d\n", thread_ids[id]);
	}

	printf("Leaving parallel region\n");
}
