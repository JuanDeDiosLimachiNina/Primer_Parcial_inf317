import multiprocessing as mp

# Función para calcular una porción de la secuencia de Fibonacci
def fibo(ini, fin):
    fb = []  # Lista para almacenar la porción de la secuencia de Fibonacci
    a, b = 0, 1
    for _ in range(ini):  # Calcular hasta el término inicial
        a, b = b, a + b
    for _ in range(fin - ini):  # Calcular y almacenar la porción correspondiente
        fb.append(a)
        a, b = b, a + b
    return fb

if __name__ == "__main__":
    N = 1000  # Número total de términos de Fibonacci
    M = mp.cpu_count()  # Cantidad de procesadores disponibles
    print("Cantidad de procesadores:", M)
    
    terms_per_process = N // M  # Calcular cuántos términos calcula cada procesador
    remainder = N % M  # Calcular los términos restantes
    print("Términos por procesador (aproximado):", terms_per_process)
    print("Términos restantes:", remainder)

    params = []
    start = 0
    for i in range(M):
        end = start + terms_per_process + (1 if i < remainder else 0)
        params.append((start, end))
        start = end

    # Crear un pool de procesos y ejecutar la función fibo en paralelo
    pool = mp.Pool()
    resultado = pool.starmap(fibo, params)
    
    # Imprimir los primeros 15 términos calculados por cada proceso
    print("Mostrando los primeros 15 términos de cada proceso")
    for i in range(len(resultado)):
        print("Proceso", i, "-->", resultado[i][:15], "....")


