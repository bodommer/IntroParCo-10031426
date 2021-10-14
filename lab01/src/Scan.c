#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main() {
	int n;
	clock_t start, end;
	double time_used;

//printf("Enter an integer between 1 and 1000000: ");

//	scanf("%d", &n);

	n = 1000000;
	int step = 10000;

	int arr1[n];
	srand(time(NULL));

	// generate array
	int j;
	for (j = 0; j < n; j++) {
	    arr1[j] = rand();
	}

	// compute prefix sum
	int i;
	for (i = 0; i < n; i = i + step) {
	       	start = clock();

		int j;
		int sum = 0;
		for (j = 0; j < i; j++) {
			int sum = 0;
			sum = sum + arr1[j];
		}

		end = clock();
		time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
		printf("%d %f \n", i, time_used);
	}
}
