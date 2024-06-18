#include <stdio.h>

// Función para sumar dos números
void suma(int *resultadoFinal, int *numero1, int *numero2) {
    *resultadoFinal = *numero1 + *numero2;
}

// Función para restar dos números
void resta(int *resultadoFinal, int *numero1, int *numero2) {
    *resultadoFinal = *numero1 - *numero2;
}

// Función para multiplicar dos números usando sumas repetidas
void multiplicacion(int *resultadoFinal, int *numero1, int *numero2) {
    *resultadoFinal = 0;
    for (int i = 0; i < *numero2; i++) {
        *resultadoFinal += *numero1;
    }
}

// Función para dividir dos números usando restas repetidas
void division(int *resultadoFinal, int *numero1, int *numero2) {
    *resultadoFinal = 0;
    int temporal = *numero1;
    while (temporal >= *numero2) {
        temporal -= *numero2;
        (*resultadoFinal)++;
    }
}

int main() {
    int numero1, numero2;
    int resultadoFinal;

    printf("Ingrese el primer número: ");
    scanf("%d", &numero1);

    printf("Ingrese el segundo número: ");
    scanf("%d", &numero2);

    suma(&resultadoFinal, &numero1, &numero2);
    printf("Suma: %d + %d = %d\n", numero1, numero2, resultadoFinal);

    resta(&resultadoFinal, &numero1, &numero2);
    printf("Resta: %d - %d = %d\n", numero1, numero2, resultadoFinal);

    multiplicacion(&resultadoFinal, &numero1, &numero2);
    printf("Multiplicación: %d * %d = %d\n", numero1, numero2, resultadoFinal);

	
    if (numero2 != 0) {
        division(&resultadoFinal, &numero1, &numero2);
        printf("División: %d / %d = %d\n", numero1, numero2, resultadoFinal);
    } else {
        printf("División: Error, división por cero.\n");
    }
    return 0;
}
