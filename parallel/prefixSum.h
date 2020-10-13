#pragma once

#include <vector>
#include <mpi.h>
#include <cmath>
#include <limits>

namespace ps
{

    int hcPrefix(int m, MPI_Comm comm)
    {
        int size, rank;
        MPI_Comm_rank(comm, &rank);
        MPI_Comm_size(comm, &size);

        int x{m};
        int sigma{m};
        int y;
        for (int k = 0; k < static_cast<int>(log2(size)); ++k)
        {
            int power = 1 << k;
            int destination = rank ^ power;
            //std::cout << "Rank: " << rank << ", partner" << destination << ", K: " << k << std::endl;
            MPI_Sendrecv(&sigma, 1, MPI_INT, destination, 0, &y, 1, MPI_INT, destination, MPI_ANY_TAG, comm, MPI_STATUS_IGNORE);
            sigma += y;
            if (rank & power)
            {
                //std::cout << rank << "hab ne 1 an stelle " << k << std::endl;
                x += y;
            }
        }
        return x;
    }
} // namespace ps