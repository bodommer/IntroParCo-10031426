#include <assert.h>
#include <mpi.h>
#include <stdio.h>

const int tag_sr = 0;

int main(int argc, char **argv){
  int rank, size, i, recv_buf, send_buf=101, buf;
  MPI_Status status;
  double tic, toc;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  assert(size==4); // To make sure there is a receiver connected and also that there is only one answer from the other side.

  tic = MPI_Wtime();
  for(i=0;i<50;i++){
    if(rank % 2 == 0){ // <-- INSERT HERE
      MPI_Send(&send_buf, 1, MPI_INT, rank+1, tag_sr , MPI_COMM_WORLD);
      MPI_Recv(&recv_buf, 1, MPI_INT, rank+1, tag_sr, MPI_COMM_WORLD, &status);
      assert(recv_buf==101);
    }else{
      MPI_Recv(&buf, 1, MPI_INT, rank-1, tag_sr, MPI_COMM_WORLD, &status);
      MPI_Send(&buf, 1, MPI_INT, rank-1, tag_sr, MPI_COMM_WORLD);
    }
  }
  toc = MPI_Wtime();

  if(rank==0)
    printf("Average time for a single message: %lf seconds (%d micro seconds)\n", (toc-tic)/100.0, (int)((toc-tic)*1.0E4));
  
  MPI_Finalize();
  return 0;
}

