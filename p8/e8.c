#include <stdio.h>
#include <omp.h> 

int main() {
    int N, M;
    printf("Ingrese cantidad de terminos de la serie a  mostrar: ");
    scanf("%d", &N); 
    
    printf("Numero de procesadores: ");
    scanf("%d", &M); 
    
    int serie[M][N]; // Definimos una matriz para almacenar la serie calculada
    
    // Región paralela utilizando OpenMP con M hilos
    #pragma omp parallel num_threads(M)
    {
        int idh = omp_get_thread_num(); // Obtenemos el ID del hilo actual
        int ini = idh * (N / M); // Calculamos el índice inicial para cada hilo
        
        // Iteramos sobre la sección de la matriz correspondiente a cada hilo
        for (int i = 0; i < N / M; i++) {
            serie[idh][i] = (ini + i + 1) * 2; // Calculamos y almacenamos los valores en la matriz
        }
    }
    
    // Imprimimos la matriz resultante
    printf("Serie:\n");
    for (int i = 0; i < M; i++) {
        printf("Procesador %d:", i);
        for (int j = 0; j < N / M; j++) {
            printf(" %d", serie[i][j]); // Imprimimos cada valor de la matriz
        }
        printf("\n");
    }
    
    return 0;
}
