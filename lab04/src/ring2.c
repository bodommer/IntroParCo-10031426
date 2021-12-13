/* Chapter 4: Non-blocking communication
 */
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
  int rank, size, i, send_buf, recv_buf, sum=0;
  MPI_Status statuses[2];
  MPI_Request requests[2];
  
  MPI_Init(&argc, &argv);
  
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  
  send_buf = rank;
  for(i=0;i<size;i++){
    MPI_Irecv(&recv_buf, 1, MPI_INT, (rank+size-1)%size, 0, MPI_COMM_WORLD, requests);
    MPI_Issend(&send_buf, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD, requests+1);
    MPI_Waitall(2, requests, statuses);
    sum+=recv_buf;
    send_buf=recv_buf;
  }

  printf("Rank %d: %d\n", rank, sum);
    
  MPI_Finalize();
  return 0;
}

