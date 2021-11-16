#define _GNU_SOURCE

#include <stdio.h>
#include <omp.h>
#include <sched.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {

	int size = 16;
	int* v1 = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++) {
		v1[i] = -1;
	}

	#pragma omp parallel
	{
		#pragma omp for //collapse(2) 
		for (int i=0; i < 4; i++) {
			for (int j=0; j < 4; j++) {
				v1[i*4 + j] = omp_get_thread_num();
			}
		}
		printf("Total thread count: %d\n", omp_get_num_threads());	
	}

	for (int i=0; i < 16; i++) {
		printf("%d ", v1[i]);
	}	

	printf("\n");


	return 0;
}
