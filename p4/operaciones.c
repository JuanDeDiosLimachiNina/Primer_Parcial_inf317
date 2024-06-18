#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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

// Función para multiplicar una matriz por un vector
void matrixVectorMultiplication(int **matrix, int *vector, int *result, int rows, int cols) {
    //paralelizando el bucle for externo
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
	//calculo del produco entre fila i de la matriz y el vector
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int N, M;

    // Solicitar al usuario que ingrese N y M
    printf("Ingrese el número de filas (N) de la matriz: ");
    scanf("%d", &N);
    printf("Ingrese el número de columnas (M) de la matriz: ");
    scanf("%d", &M);

    // Inicializar la matriz y el vector con valores aleatorios
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 10; // Valores aleatorios entre 0 y 9
        }
    }

    int *vector = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        vector[i] = rand() % 10; // Valores aleatorios entre 0 y 9
    }

    // Imprimir la matriz y el vector
    printMatrix(matrix, N, M);
    printf("\n");
    printVector(vector, M);
    printf("\n");

    // Realizar la multiplicación de matriz por vector
    int *result = (int *)malloc(N * sizeof(int));
    matrixVectorMultiplication(matrix, vector, result, N, M);

    // Imprimir el resultado
    printf("Resultado de la multiplicación de matriz por vector:\n");
    printVector(result, N);

    // Liberar memoria
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}
