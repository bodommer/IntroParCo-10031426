#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main() {
	int n;
	clock_t start, end;
	double time_used;

//printf("Enter an integer between 1 and 2147483647: ");

//	scanf("%d", &n);

        int step = 100;
	int max_size = 100000;
	int arr1[max_size];
	int arr2[max_size];
	int result[max_size];
	srand(time(NULL));

	for (n = step; n < max_size; n = n + step) {
		start = clock();

		int i;
		for(i = 0; i < n; i++) {
		    arr1[i] = rand();
		    arr2[i] = rand();
		}
		int j;
		for (j = 0; j < n; j++) {
		    result[j] = arr1[j] + arr2[j];
		}

		end = clock();
		time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
		printf("%d %f \n", n, time_used);
	}
}
