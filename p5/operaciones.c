#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 2 // Número de filas de la matriz y longitud del vector
#define M 2 // Número de columnas de la matriz

// Función para imprimir una matriz
void printMatrix(int **matrix, int rows, int cols) {
    printf("Matriz:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Función para imprimir un vector
void printVector(int *vector, int size) {
    printf("Vector:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", vector[i]);
    }
}

// Función para multiplicar una matriz NxM por un vector de longitud N
void matrixVectorMultiplication(int **matrix, int *vector, int *result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != N) {
        if (rank == 0) {
            printf("El número de procesos debe ser igual al número de filas de la matriz.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int **matrix = NULL;
    int *vector = NULL;
    int *result = NULL;

    // Proceso 0 inicializa la matriz y el vector
    if (rank == 0) {
        matrix = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            matrix[i] = (int *)malloc(M * sizeof(int));
            for (int j = 0; j < M; j++) {
                matrix[i][j] = rand() % 10; // Valores aleatorios entre 0 y 9
            }
        }

        vector = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            vector[i] = rand() % 10; // Valores aleatorios entre 0 y 9
        }

        result = (int *)malloc(N * sizeof(int));
    }

    // Distribuir la matriz y el vector a todos los procesos
    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < N; j++) {
                MPI_Send(matrix[j], M, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        matrix = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            matrix[i] = (int *)malloc(M * sizeof(int));
            MPI_Recv(matrix[i], M, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    // Realizar la multiplicación de matriz por vector
    int *partialResult = (int *)malloc(N * sizeof(int));
    matrixVectorMultiplication(matrix, vector, partialResult, N, M);

    // Recolectar los resultados parciales y sumarlos en el proceso 0
    MPI_Reduce(partialResult, result, N, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Imprimir el resultado desde el proceso 0
    if (rank == 0) {
        // Imprimir la matriz y el vector
        printMatrix(matrix, N, M);
        printf("\n");
        printVector(vector, N);
        printf("\n");

        // Imprimir el resultado de la multiplicación
        printf("Resultado de la multiplicación de matriz por vector:\n");
        printVector(result, N);

        // Liberar memoria
        for (int i = 0; i < N; i++) {
            free(matrix[i]);
        }
        free(matrix);
        free(vector);
        free(result);
    }

    MPI_Finalize();

    return 0;
}
