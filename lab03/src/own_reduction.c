#define _GNU_SOURCE

#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

void print_arr(int** arr, int lines, int rows) {
	for (int i = 0; i < lines; i++) {
		printf("[ ");
		for (int j = 0; j < rows; j++ ){
			printf("%d ", arr[i][j]);
		}
		printf(" ]\n");
	}
}

int main(int argc, char* argv[]) {

	clock_t time1;
	clock_t time2;

	if (argc < 2) {
		printf("Insufficient argument count!");
		return -1;
	}
	
	int size = atoi(argv[1]);

	int nthreads;
	#pragma omp parallel shared(nthreads)
	{
		#pragma omp single
		{
			nthreads = omp_get_num_threads();
		}
	}

	// iterations mofified by -1 because we don't use the last array for storing thread results
	int iterations = (int) (ceil(log(size/nthreads) / log(2)) + 1) - 1;
	int** arr = malloc(sizeof(int*) * iterations);
	for (int i=0; i < iterations; i++) {
		arr[i] = malloc(size * sizeof(int));
	}

	srand(123);
	for (int i=0; i < size; i++) {
		arr[0][i] = rand() % (INT_MAX / 2);
		//arr[0][i] = i;
	}

	for (int j = 0; j < size; j++) {
		for (int i = 1; i < iterations; i++) {
			arr[i][j] = 0;
		}
	}

	// sequential counting - reference result
	int res = 0;
	time1 = clock();
	for (int i=0; i < size; i++) {
		res += arr[0][i];
	}
	time1 = clock() - time1;

	//print_arr(arr, iterations, size);

	int result = 0;
	static int thread_id = -1;
	
	#pragma omp threadprivate(thread_id)

	// set to -1 to switch debugging off
	int analyzed_thread = -1;

	time2 = clock();
	#pragma omp parallel shared(result, iterations, arr)
	{
		thread_id = omp_get_thread_num();
	
		for (int iter = 0; iter < iterations; iter++) {
			int stride = pow(2, iter);
			int step = nthreads * stride;
			if (thread_id == analyzed_thread) {
				printf("Step: %d, nthreads: %d, stride: %d\n", step, nthreads, stride);
			}

			for (int k=0; (k + 1) * step + thread_id < size; k = k + 2) {
				int left_index = k * step + thread_id;
				int right_index = (k + 1) * step  + thread_id;
				if (thread_id == analyzed_thread) {
					printf("Summing %d:%d and %d:%d into %d:%d\n", iter, left_index, iter, right_index, iter+1, left_index);
				}
				if (iter == iterations - 1) {
					if (thread_id == analyzed_thread) {
						printf("last iteration: %d:%d + %d:%d\n", iter, left_index, iter, right_index);
					}
					int r = arr[iter][left_index] + arr[iter][right_index];

					if (thread_id == analyzed_thread) {
						printf("Last result for thread %d: %d\n", thread_id, r);
					}
					
					#pragma omp critical
					result += r;
				} else {
					arr[iter+1][left_index] =  arr[iter][left_index] + arr[iter][right_index];
				}
				
				if (thread_id == analyzed_thread && iter < iterations - 2) {
					printf("%d + %d = %d\n", arr[iter][left_index], arr[iter][right_index], arr[iter+1][left_index]);
				}
			}
	//		print_arr(arr, iterations, size);
		}
	}
	time2 = clock() - time2;

	//printf("Sequential result: %d\nParallel result: %d\n", res, result);

        printf("%d,%f,%f\n", size, ((double) time1)/CLOCKS_PER_SEC, ((double) time2)/CLOCKS_PER_SEC);

	return 0;
}
