#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    int size;
    int consumo;
    int consumo_total;
    int consumo_maximo;
    int consumo_minimo;

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
        consumo = 150;
    } else if (rank == 1) {
        consumo = 120;
    } else if (rank == 2) {
        consumo = 180;
    } else {
        consumo = 100;
    }

    printf("Proceso %d: consumo = %d kWh\n", rank, consumo);

    MPI_Reduce(&consumo, &consumo_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Reduce(&consumo, &consumo_maximo, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Reduce(&consumo, &consumo_minimo, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nConsumo total: %d kWh\n", consumo_total);
        printf("Consumo maximo: %d kWh\n", consumo_maximo);
        printf("Consumo minimo: %d kWh\n", consumo_minimo);
    }

    MPI_Finalize();
    return 0;
}
