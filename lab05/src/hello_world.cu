#include <stdio.h>
#include <stdlib.h>

__global__ void printf_from_gpu(void) {
	printf("Hello, world! From thread [%d, %d] From device\n", threadIdx.x, blockIdx.x);
}

int main(void) {
	printf("Hello, world from host!\n");
	printf_from_gpu<<<2,1>>>();
	cudaDeviceSynchronize();
	return 0;
}
