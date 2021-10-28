#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "mpi.h"
int sched_getcpu();

/* This code is adapted from an example at:
 * http://brokestream.com/procstat.html */
int get_cpu_id()
{
	int i;
	FILE* procfile = fopen("/proc/self/stat", "r");
	long to_read = 8192;
	char buffer[to_read];
	int read = fread(buffer, sizeof(char), to_read, procfile);
	fclose(procfile);

	// Field with index 38 (zero-based counting) is the one we want
	char* line = strtok(buffer, " ");
	for (i = 1; i < 38; i++)
	{
		line = strtok(NULL, " ");
	}

	line = strtok(NULL, " ");
	int cpu_id = atoi(line);
	return cpu_id;
}

int main (int argc, char *argv[])
{
  int id, np;
  char name[MPI_MAX_PROCESSOR_NAME];
  int namelen;
  char filename[128], filename_threads[128];
  FILE *fil, *fil_threads;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &np);
  MPI_Comm_rank (MPI_COMM_WORLD, &id);
  MPI_Get_processor_name (name, &namelen);

  sprintf (filename, "nodesused-%d.log", id);
  fil = fopen (filename, "w");
  if (fil == NULL)
  {
    fprintf (stderr, "nodesused: problem opening file %s\n", filename);
    exit(1);
  }
  fprintf(fil, "MPI process %04d of %04d on cpu_id %02d of node %4s\n",
  id, np, sched_getcpu(), name);
  MPI_Barrier(MPI_COMM_WORLD);
  fflush (fil);
  fclose (fil);
#ifdef _OPENMP
  sprintf (filename_threads, "nodesused_threads-%d.log", id);
  fil_threads = fopen(filename_threads, "w");
  if(fil_threads == NULL)
  {
    fprintf (stderr, "nodesused: problem opening file %s\n", filename_threads);
    exit(1);
  }
  #pragma omp parallel
  {
    fprintf(fil_threads,
    "MPI process %04d of %04d thread %02d of %02d on cpu_id %02d of node %4s\n",
    id, np, omp_get_thread_num(), omp_get_num_threads(),
    sched_getcpu(), name);
  }
  #pragma omp barrier
  fflush (fil_threads);
  fclose (fil_threads);
#endif
