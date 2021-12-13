/* Chapter 4: Non-blocking communications.
 */
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
  int rank, size, i, send_buf, recv_buf, sum=0;
  MPI_Status wait_status;
  MPI_Request send_request, recv_request;
  
  MPI_Init(&argc, &argv);
  
  MPI_Comm_rank (MPI_COMM_WORLD, &rank); // <-- INSERT HERE
  MPI_Comm_size (MPI_COMM_WORLD, &size); // <-- INSERT HERE
  
  send_buf = rank;
  for(i=0;i<size;i++){
    MPI_Isend(&send_buf, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD, &send_request); // <-- INSERT HERE
    MPI_Irecv(&recv_buf, 1, MPI_INT, (rank+size-1)%size, 0, MPI_COMM_WORLD, &recv_request); // <-- INSERT HERE
    MPI_Wait(&send_request, &wait_status); // <-- INSERT HERE
    MPI_Wait(&recv_request, &wait_status);
    sum+=recv_buf;
    send_buf=recv_buf;
  }

  printf("Rank %d: %d\n", rank, sum);
    
  MPI_Finalize();
  return 0;
}

