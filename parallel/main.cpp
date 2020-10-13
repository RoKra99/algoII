#include <mpi.h>
#include "prefixSum.h"

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int prefixSum = ps::hcPrefix(rank, MPI_COMM_WORLD);
    std::cout << "P" << rank << " , ps: " << prefixSum << std::endl;
    MPI_Finalize();
}