#define _GNU_SOURCE

#include <stdio.h>
#include <omp.h>
#include <sched.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {

	int threads = 0;

	int threads2 = 0;

	#pragma omp parallel 
	{
		#pragma omp parallel num_threads(2)
		{

		#pragma omp atomic 
			threads++;

		threads2 = omp_get_num_threads();
		int thread_num = omp_get_thread_num();
		printf("Working on thread: %d\n", thread_num);
		cpu_set_t mask;

		CPU_ZERO(&mask);
		sleep(3);
		int cpu_num = sched_getcpu();
		printf("Thread %3d is running on CPU %3d\n", thread_num, cpu_num);
		}
	}

	printf("Total thread count: %d\n", threads);
	printf("Total thread2 count: %d\n", threads2);

	return 0;
}
