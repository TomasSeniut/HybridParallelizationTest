//
// Created by tomas on 18.12.10.
//

#include <malloc.h>
#include <mpi.h>

#define N 10

typedef struct abc {
    float ffloat;
    int iint;
    int *taken;
} stack_data;

MPI_Datatype MpiStackData(int n) {
    MPI_Datatype mpi_stack_type;
    MPI_Datatype types[2] = {MPI_FLOAT, MPI_INT};
    int blocklengths[2] = {1, 1};
    MPI_Aint offsets[2];

    offsets[0] = offsetof(stack_data, ffloat);
    offsets[1] = offsetof(stack_data, iint);

    MPI_Type_create_struct(2, blocklengths, offsets, types, &mpi_stack_type);
    MPI_Type_commit(&mpi_stack_type);

    return mpi_stack_type;
}

int sendStruct() {

    MPI_Init(NULL, NULL);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Datatype stack_type = MpiStackData(N);

    if (rank == 0) {
        for (int j = 0; j < 3; ++j) {
            stack_data p;
            p.ffloat = 123.43;
            p.iint = 4440 + j;
            p.taken = malloc(N * sizeof(int));
            for (int i = 0; i < N; ++i) {
                p.taken[i] = i * i + j;
            }

            //Send
            printf("Sending\n");
            MPI_Send(&p, 1, stack_type, 1, 0, MPI_COMM_WORLD);
            MPI_Send(p.taken, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
            printf("Sent\n");
        }

    } else if (rank == 1) {

        for (int j = 0; j < 3; ++j) {
            //receive and print
            stack_data c;
            c.taken = malloc(N * sizeof(int));

            printf("receiving\n");
            MPI_Recv(&c, 1, stack_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(c.taken, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("Received: ffloat: %f, iint: %d\n", c.ffloat, c.iint);
            for (int i = 0; i < N; ++i) {
                printf("%d ", c.taken[i]);
            }
            printf("\n");
        }
    }

    MPI_Type_free(&stack_type);
    MPI_Finalize();
}