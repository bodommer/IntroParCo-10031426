#define _GNU_SOURCE

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

int main(int argc, char* argv[]) {

	clock_t time1;
	clock_t time2;

	if (argc < 2) {
		printf("Insufficient argument count!");
		return -1;
	}

	int size = atoi(argv[1]);
	//printf("size: %d\n", size);

	int* arr = malloc(sizeof(int) * size);

	srand(123);
	for (int i=0; i < size; i++) {
		arr[i] = rand() % (INT_MAX / 2);
	}

	int sum2 = 0;
	time2 = clock();
	for (int i=0; i < size; i++) {
		sum2 += arr[i];
	}
	time2 = clock() - time2;
	
	int sum = 0;

	time1 = clock();
	#pragma omp parallel shared(sum)
	{
		#pragma omp for reduction(+:sum)
		for (int i = 0; i < size; i++) {
			sum += arr[i];
		}
	}	
	time1 = clock() - time1;
	
	assert(sum == sum2);

	printf("%d,%f,%f\n", size, ((double) time1)/CLOCKS_PER_SEC, ((double) time2)/CLOCKS_PER_SEC);

	return 0;
}
