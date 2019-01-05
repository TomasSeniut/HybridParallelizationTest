//
// Created by tomas on 18.12.9.
//

#include <mpi.h>
#include <stdio.h>
#include <omp.h>
#include "IO.h"

int simpleMPITest() {

    int provided;
    MPI_Init_thread(NULL, NULL, MPI_THREAD_SERIALIZED, &provided);
    printf("Provided level: %d\n", provided);

    data info = ReadData();

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    #pragma omp parallel
    {
        #pragma omp critical
        {
            printf("Hello from %d/%d process,  thread: %d/%d ", world_rank, world_size, omp_get_thread_num(),
                   omp_get_num_threads());
            printf("I found numbers: ");
            for (int i = 0; i < info.size; ++i) {
                printf("%d ", info.array[i]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
}