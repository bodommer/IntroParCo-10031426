#pragma GCC ivde

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
	int n = atoi(argv[1]);
	clock_t start, end;
	double time_used;

//printf("Enter an integer between 1 and 2147483647: ");

//	scanf("%d", &n);

        int nthreads = 0;
        int tid = 0;
        #pragma omp parallel private(nthreads, tid)
        {
                tid = omp_get_thread_num();
                nthreads = omp_get_num_threads();
                if (tid == 0) {
                        fprintf(stderr, "Computing XXX using %d threads per \n", nthreads);
                }
        }

        int step = 100;
	int max_size = 100000;
	int* arr1 = malloc(n * sizeof(int));
	int* arr2 = malloc(n * sizeof(int));
	int* result = malloc(n * sizeof(int));
	srand(time(NULL));

	//int k;
	//for (k = step; k < n; k = k + step) {
		start = clock();

		int i;
		for(i = 0; i < n; i++) {
		    arr1[i] = rand();
		    arr2[i] = rand();
		}
		int j;
		#pragma omp for
		for (j = 0; j < n; j++) {
		    result[j] = arr1[j] + arr2[j];
		}

		end = clock();
		time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
		printf("%d;%f\n", n, time_used);
	//}
}
