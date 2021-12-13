#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

__global__ void VecAdd(int* A, int* B, int* C, int N) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if (i < N)
		C[i] = A[i] + B[i];
}

int main(int argc, char* argv[]) {
	int block = atoi(argv[2]);

	int power = atoi(argv[1]);
	int arr_size = pow(2, power);

	//printf("block count: %d, threads in block: %d, array_size: %d\n", block, arr_size/block, arr_size);

	srand(123);
	
	cudaEvent_t start, stop;

	int* A, *B, *C, *D;
	A = (int*) malloc(sizeof(int) * arr_size);
	B = (int*) malloc(sizeof(int) * arr_size);
	C = (int*) malloc(sizeof(int) * arr_size);	
	D = (int*) malloc(sizeof(int) * arr_size);
	
	for (int i=0; i < arr_size; i++) {
		A[i] = rand() % (arr_size/2);
		B[i] = rand() % (arr_size/2);
		C[i] = 0;
		D[i] = A[i] + B[i];
	}

	int* devA, *devB, *devC;
	cudaMalloc((void**)&devA, sizeof(int) * arr_size);
	cudaMalloc((void**)&devB, sizeof(int) * arr_size);
	cudaMalloc((void**)&devC, sizeof(int) * arr_size);

	cudaMemcpy(devA, A, sizeof(int) * arr_size, cudaMemcpyHostToDevice);
        cudaMemcpy(devB, B, sizeof(int) * arr_size, cudaMemcpyHostToDevice);	
	
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaEventRecord(start);
	VecAdd<<<block,arr_size/block>>>(devA, devB, devC, arr_size);
	cudaError_t kernel_error = cudaGetLastError();
	cudaEventRecord(stop);

	float runtime = 0.0f;
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&runtime, start, stop);

	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	
	if (kernel_error != cudaSuccess) {
		printf("LastError: %s\nDetails: %s\n", cudaGetErrorName(kernel_error), cudaGetErrorString(kernel_error));
		printf("ERROR: array %d - %d blocks\n", arr_size, block);
	} else {
		cudaMemcpy(C, devC, sizeof(int) *arr_size, cudaMemcpyDeviceToHost);

		for (int i=0; i < 5; i++) {
			int r = rand() % arr_size;
			//printf("r: %d, C: %d, D: %d\n", r, C[r], D[r]);
			assert(C[r] == D[r]);
		}
		printf("%d;%d;%f\n", arr_size, block, runtime);
		//printf("OK: array %d - %d blocks\n", arr_size, block);
	}

	free(A);
	free(B);
	free(C);
	free(D);
	cudaFree(devA);
	cudaFree(devB);
	cudaFree(devC);

	return kernel_error;
}
