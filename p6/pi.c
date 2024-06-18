#include <stdio.h>
#include <mpi.h>
#include <math.h>

//utilizando la Identidad de euler:
//π⁴/90 = 1/1⁴ + 1/2⁴ + 1/3⁴ + 1/4⁴+...
double euler(int x) {
    return 1.0/pow(x, 4);
}

int main (int argc, char** argv){
	int proc, cant, N=100000;
	double suma = 0.0, sum_total = 0.0;
  
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc);
	MPI_Comm_size(MPI_COMM_WORLD, &cant);
	

    for (int i = proc + 1; i <= N; i += cant) {
        suma += euler(i);
    }

    // Reducir las sumas parciales en la suma total en el proceso principal
    MPI_Reduce(&suma, &sum_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (proc == 0) {
        double pi = pow(90 * sum_total, 0.25);
        printf("EL VALOR DE PI ES APROXIMADAMENTE: %.16f\n", pi);
    }
    
	MPI_Finalize();
}
