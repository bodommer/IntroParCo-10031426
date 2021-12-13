#include <assert.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  char *buf=NULL;
  int rank, size, i, nbytes=0;
  MPI_Status status; // <-- INSERT HERE
  double tic, toc; // <-- INSERT HERE
  
  /* Process arguments. */

  MPI_Init(&argc, &argv);
  assert((argc==1)||(argc==2));
  if(argc==2){
    nbytes = atoi(argv[1]);
    buf = (char *)malloc(nbytes);
    assert(buf!=NULL);
  }

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  assert(size==2);
  
  tic = MPI_Wtime() ; // <-- INSERT HERE
 
  printf("sending\n");

  for(i=0;i<50;i++){
    if(rank % 2 == 0){ // <-- INSERT HERE
      //printf("0: send\n");
      MPI_Send(buf, nbytes, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
      //printf("0: recv\n");

      MPI_Recv(buf, nbytes, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
    }else{
      //printf("1: send\n");
      MPI_Recv(buf, nbytes, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
      //printf("1: recv\n");
      MPI_Send(buf, nbytes, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
  }
  toc = MPI_Wtime(); // <-- INSERT HERE

  if(nbytes!=0)
    free(buf);

  //if(rank == 0){ // <-- INSERT HERE
    if(nbytes==0)
      printf("%d: Latency: %d micro-seconds\n", rank, (int)((toc-tic)*1.0E4));
    else
      printf("%d: Bandwidth: %d bytes/sec\n", rank, (int)(nbytes/((toc-tic)/100.0)));
  //}
  
  MPI_Finalize();
  return 0;
}

