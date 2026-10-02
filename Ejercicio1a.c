#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    int size;
    float temperatura;
    float temperaturas[4];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {

        if (rank == 0) {
            printf("Este programa requiere exactamente 4 procesos.\n");
        }

        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        temperatura = 24.5;
    } else if (rank == 1) {
        temperatura = 26.1;
    } else if (rank == 2) {
        temperatura = 23.8;
    } else {
        temperatura = 27.0;
    }

    printf("Proceso %d: temperatura registrada = %.1f C\n",
           rank, temperatura);

    MPI_Gather(
        &temperatura,
        1,
        MPI_FLOAT,
        temperaturas,
        1,
        MPI_FLOAT,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {

        printf("\nOficina Central: temperaturas recibidas\n");

        for (int i = 0; i < size; i++) {
            printf("Proceso %d: %.1f C\n", i, temperaturas[i]);
        }
    }

    MPI_Finalize();

    return 0;
}