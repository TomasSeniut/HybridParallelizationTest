//
// Created by tomas on 18.12.11.
//

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int notifyProcesses() {

    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(4);

    if (rank == 0) {
        int try = 0;
        int random = 0;
        while (random < 90) {
            try++;
            random = rand() % 100;

            if (random > 90) {
                printf("Found %d on try %d and Sending to processes\n", random, try);
                for (int i = 0; i < size; ++i) {
                    if (i == rank) continue;

                    MPI_Send(&random, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                }
            }
        }

    } else {
        int received = 0;

        while (!received) {

            int flag;
            MPI_Status status;
            MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);

            if (flag) {
                printf("Found message on process: %d, from %d with tag: %d\n", rank, status.MPI_SOURCE, status.MPI_TAG);

                int mess;
                MPI_Recv(&mess, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Message %d received on %d\n", mess, rank);

                received = 1;
            }
        }
    }

    MPI_Finalize();
}