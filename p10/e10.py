import multiprocessing as mp
import math as m

# Define la función  que genera la serie 2, 4, 6, 8, 10, 12, ...
def genera_serie(ini, fin): 
    v = []
    for i in range(ini, fin):
        v.append(i * 2 + 2)
    return v

if __name__ == "__main__":
    N = int(input("Introduzca cantidad de términos N: ")) 
    M = mp.cpu_count()  # Obtiene el número de procesadores disponibles
    print("Cantidad de procesadores:", M)
    
    N //= M  # Divide N entre M para calcular el número de términos que cada proceso manejará
    
    # Define los parámetros para cada proceso basado en la división de N
    params = [(i * N, N * (i + 1)) for i in range(M)]
    
    pool = mp.Pool()  # Crea un grupo de procesos
    resultado = pool.starmap(genera_serie, params)  # Ejecuta la función con los parámetros dados
    for i in range(len(resultado)):
        print("Proceso", i, ":", resultado[i])  # Imprime el resultado de cada proceso
