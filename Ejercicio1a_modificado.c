
#include <stdio.h>
#include <mpi.h>

#define NUM_MEDICIONES 2
#define NUM_PROCESOS   4

int main(int argc, char *argv[]) {

    int rank;
    int size;
    float temperaturas_locales[NUM_MEDICIONES];
    float temperaturas[NUM_PROCESOS * NUM_MEDICIONES];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != NUM_PROCESOS) {
        if (rank == 0) {
            printf("Este programa requiere exactamente 4 procesos.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        temperaturas_locales[0] = 24.5;
        temperaturas_locales[1] = 25.0;
    } else if (rank == 1) {
        temperaturas_locales[0] = 26.1;
        temperaturas_locales[1] = 26.4;
    } else if (rank == 2) {
        temperaturas_locales[0] = 23.8;
        temperaturas_locales[1] = 24.1;
    } else {
        temperaturas_locales[0] = 27.0;
        temperaturas_locales[1] = 27.3;
    }

    printf("Proceso %d: temperaturas registradas = %.1f C, %.1f C\n",
           rank, temperaturas_locales[0], temperaturas_locales[1]);

    MPI_Gather(
        temperaturas_locales,
        NUM_MEDICIONES,
        MPI_FLOAT,
        temperaturas,
        NUM_MEDICIONES,
        MPI_FLOAT,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        printf("\nOficina Central: temperaturas recibidas\n");
        for (int i = 0; i < size; i++) {
            printf("Proceso %d: %.1f C, %.1f C\n", i,
                   temperaturas[i * NUM_MEDICIONES],
                   temperaturas[i * NUM_MEDICIONES + 1]);
        }
    }

    MPI_Finalize();
    return 0;
}
