#include <mpi.h>

#include "control.h"

int main(int argc, char *argv[])
{
  int mpiThreads;
  int mpiThreadRank;
  MPI_Status mpiStatus;
  Control *control;
  Fragment *fragment;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpiThreadRank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpiThreads);
  if(mpiThreadRank == 0) // main control thread
  {
    fprintf(stdout, "%i\n", mpiThreadRank);
    control = new Control(mpiThreads - 1);
    control->execute();
    delete control;
  }
  else // fragments
  {
    fragment = new Fragment;
  }
  MPI_Finalize();

  return 0;
}
