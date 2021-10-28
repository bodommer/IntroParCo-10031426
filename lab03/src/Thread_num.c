#define _GNU_SOURCE

#include <stdio.h>
#include <omp.h>
#include <sched.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {

	void print_affinity(int pid) {
    cpu_set_t mask;
    long nproc, i;

    if (sched_getaffinity(pid, sizeof(cpu_set_t), &mask) == -1) {
//perror("sched_getaffinity");
  //      assert(false);
  	printf("AAAA\n");
    }
    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    printf("sched_getaffinity %d  = ", pid);
    for (i = 0; i < nproc; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");
}

	#pragma omp parallel 
	{
		int thread_num = omp_get_thread_num();
		printf("Working on thread: %d\n", thread_num);
		cpu_set_t mask;

		print_affinity(thread_num);

		CPU_ZERO(&mask);
		CPU_SET(thread_num, &mask);
		if (sched_setaffinity(thread_num, sizeof(cpu_set_t), &mask) == -1) {
			printf("ERROR, core %d\n", thread_num);
		}	
		print_affinity(thread_num);
		sleep(3);
		int cpu_num = sched_getcpu();
		printf("Thread %3d is running on CPU %3d\n", thread_num, cpu_num);
	}
	return 0;
}
