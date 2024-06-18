#include <stdio.h>
#include <omp.h>
#include <math.h>

// Función para verificar si un número es entero
int es_entero(double numero) {
    return floor(numero) == numero;
}

// Función para multiplicar dos números usando sumas repetidas con OpenMP
double multiplicacion_openmp(double numero1, double numero2) {
    double resultadoFinal = 0.0;
    int parteEntera = (int)numero2; // parte entera del multiplicadors
    int parteDecimal = numero2 - parteEntera;// parte decimal del multiplicador
//multipkiacaion  de la parte entera
    #pragma omp parallel for reduction(+:resultadoFinal)
    for (int i = 0; i < parteEntera; i++) {
        resultadoFinal += numero1;
    }
    //multipliacacion de la parte decimal
    resultadoFinal += numero1 * parteDecimal;
    return resultadoFinal;
}

// Función para dividir dos números usando restas repetidas con OpenMP
double division_openmp(double numero1, double numero2) {
    double resultadoFinal = 0.0;
    double temporal = numero1;
    double paso = 0.1; // Precisión del resultado a un decimal
    #pragma omp parallel
    {
        while (temporal >= numero2) {
            #pragma omp critical
            {
                if (temporal >= numero2) {
                    temporal -= numero2;
                    resultadoFinal++;
                }
            }
        }
        // Manejo del residuo
        while (temporal >= numero2 * paso) {
            #pragma omp critical
            {
                if (temporal >= numero2 * paso) {
                    temporal -= numero2 * paso;
                    resultadoFinal += paso;
                }
            }
        }
    }
    return resultadoFinal;
}

int main() {
    double numero1, numero2;
    double resultadoMultiplicacion, resultadoDivision;

    // Leer los números desde la consola
    printf("Ingrese el primer número: ");
    scanf("%lf", &numero1);

    printf("Ingrese el segundo número: ");
    scanf("%lf", &numero2);

    // Realizar la multiplicación utilizando OpenMP
    resultadoMultiplicacion = multiplicacion_openmp(numero1, numero2);
    if (es_entero(numero1) && es_entero(numero2)) {
        printf("Multiplicación con OpenMP: %.0lf * %.0lf = %.0lf\n", numero1, numero2, resultadoMultiplicacion);
    } else {
        printf("Multiplicación con OpenMP: %.1lf * %.1lf = %.1lf\n", numero1, numero2, resultadoMultiplicacion);
    }

    // Realizar la división utilizando OpenMP
    if (numero2 != 0) {
        resultadoDivision = division_openmp(numero1, numero2);
        if (es_entero(numero1) && es_entero(numero2)) {
            printf("División con OpenMP: %.0lf / %.0lf = %.1lf\n", numero1, numero2, resultadoDivision);
        } else {
            printf("División con OpenMP: %.1lf / %.1lf = %.1lf\n", numero1, numero2, resultadoDivision);
        }
    } else {
        printf("División: Error, división por cero.\n");
    }

    return 0;
}
