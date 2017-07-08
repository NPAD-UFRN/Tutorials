#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
  int  rank, comm_sz, len;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Get_processor_name(hostname, &len);
  printf ("Hello from process %d on node %s!\n", rank, hostname);
  if (rank == 0)
    printf("From process %d: Number of MPI processes is %d\n", rank, comm_sz);

  MPI_Finalize();
}