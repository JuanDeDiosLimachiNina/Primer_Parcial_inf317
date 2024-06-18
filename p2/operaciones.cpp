#include <iostream>

class Operaciones {
public:
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
};

int main() {
    int numero1, numero2;
    int resultadoFinal;

    std::cout << "Ingrese el primer número: ";
    std::cin >> numero1;

    std::cout << "Ingrese el segundo número: ";
    std::cin >> numero2;

    // Crear instancia de la clase Operaciones
    Operaciones operaciones;

    // Realizar las operaciones utilizando los métodos de la clase Operaciones
    operaciones.suma(&resultadoFinal, &numero1, &numero2);
    std::cout << "Suma: " << numero1 << " + " << numero2 << " = " << resultadoFinal << std::endl;

    operaciones.resta(&resultadoFinal, &numero1, &numero2);
    std::cout << "Resta: " << numero1 << " - " << numero2 << " = " << resultadoFinal << std::endl;

    operaciones.multiplicacion(&resultadoFinal, &numero1, &numero2);
    std::cout << "Multiplicación: " << numero1 << " * " << numero2 << " = " << resultadoFinal << std::endl;

    if (numero2 != 0) {
        operaciones.division(&resultadoFinal, &numero1, &numero2);
        std::cout << "División: " << numero1 << " / " << numero2 << " = " << resultadoFinal << std::endl;
    } else {
        std::cout << "División: Error, división por cero." << std::endl;
    }

    return 0;
}

