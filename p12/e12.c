#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define REQUEST_TERM 1  // Etiqueta para enviar solicitud de cálculo de término
#define TERM_RESPONSE 2 // Etiqueta para enviar respuesta con el término calculado
#define END_WORK 3      // Etiqueta para finalizar el trabajo de los SLAVES

// Función para calcular el n-ésimo término de Fibonacci
unsigned long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main(int argc, char* argv[]) {
    int proc, cant, N, MASTER = 0;

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc); // Obtener el rango (ID) del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &cant); // Obtener el número total de procesos

    if (proc == MASTER) { // Código para el proceso MASTER
        // Solicitar el número de términos de Fibonacci a calcular
        printf("Introducir N: ");
        fflush(stdout); // Asegurar que el mensaje se imprima antes de leer la entrada
        scanf("%d", &N);
        printf("\n");

        // Reservar memoria para almacenar la secuencia de Fibonacci
        unsigned long long *fib_sequence = malloc(N * sizeof(unsigned long long));
        int term_index = 0;

        // Enviar solicitudes iniciales a los procesos SLAVE
        for (int i = 1; i < cant && term_index < N; ++i) {
            MPI_Send(&term_index, 1, MPI_INT, i, REQUEST_TERM, MPI_COMM_WORLD);
            ++term_index;
        }

        // Mientras haya términos pendientes de calcular
        while (term_index < N) {
            unsigned long long term;  // Variable para almacenar el término de Fibonacci calculado
            int received_index;       // Variable para almacenar el índice del término recibido
            MPI_Status status;        // Estado del mensaje recibido

            // Recibir el término calculado por un proceso SLAVE
            MPI_Recv(&term, 1, MPI_UNSIGNED_LONG_LONG, MPI_ANY_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);
            MPI_Recv(&received_index, 1, MPI_INT, status.MPI_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);

            // Almacenar el término recibido en la secuencia de Fibonacci
            fib_sequence[received_index] = term;

            // Enviar nueva solicitud al proceso SLAVE que acaba de responder
            MPI_Send(&term_index, 1, MPI_INT, status.MPI_SOURCE, REQUEST_TERM, MPI_COMM_WORLD);
            ++term_index;  // Incrementar el índice del término
        }

        // Recoger los resultados restantes de los procesos SLAVE
        for (int i = 1; i < cant; ++i) {
            unsigned long long term;  // Variable para almacenar el término de Fibonacci calculado
            int received_index;       // Variable para almacenar el índice del término recibido
            MPI_Status status;        // Estado del mensaje recibido

            // Recibir el término calculado por un proceso SLAVE
            MPI_Recv(&term, 1, MPI_UNSIGNED_LONG_LONG, MPI_ANY_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);
            MPI_Recv(&received_index, 1, MPI_INT, status.MPI_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);

            // Almacenar el término recibido en la secuencia de Fibonacci
            fib_sequence[received_index] = term;
        }


        // Enviar señal de finalización a todos los procesos SLAVE
        for (int i = 1; i < cant; ++i) {
            MPI_Send(0, 0, MPI_INT, i, END_WORK, MPI_COMM_WORLD);
        }

        // Imprimir la secuencia completa de Fibonacci
        printf("Secuencia de los %d terminos: ", N);
        for (int i = 0; i < N; ++i) {
            printf("%llu ", fib_sequence[i]);
        }
        printf("\n");

        // Liberar memoria
        free(fib_sequence);

    } else { // Código para los procesos SLAVE
        while (1) {
            int term_index;
            MPI_Status status;

            // Recibir solicitud del proceso MASTER
            MPI_Recv(&term_index, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            // Si la etiqueta es END_WORK, salir del bucle
            if (status.MPI_TAG == END_WORK) {
                break;
            }

            // Calcular el término de Fibonacci solicitado
            unsigned long long term = fibonacci(term_index);

            // Enviar el término calculado y su índice de vuelta al proceso MASTER
            MPI_Send(&term, 1, MPI_UNSIGNED_LONG_LONG, MASTER, TERM_RESPONSE, MPI_COMM_WORLD);
            MPI_Send(&term_index, 1, MPI_INT, MASTER, TERM_RESPONSE, MPI_COMM_WORLD);
        }
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
