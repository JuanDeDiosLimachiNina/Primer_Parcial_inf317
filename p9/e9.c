#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int proc, cant, N, i;
    
    printf("Numero de terminos: ");
	scanf("%d",&N);
	
	int serie[8][N]; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);
    MPI_Comm_size(MPI_COMM_WORLD, &cant);


    for (int pr = 0; pr < cant; pr++){
        int ini = pr * (N/cant);
		for (i = 0; i < N/cant; i++)
		    serie[pr][i] = (ini + i + 1) * 2;
	}
            
    
    if(proc==0){
		printf("Serie:\n");
		for (i = 0; i < cant; i++) {
		    printf("Procesador %d:", proc);
		    for (int j = 0; j < N/cant; j++)
		        printf(" %d", serie[i][j]);
		    printf("\n");
		}
	}
    
    MPI_Finalize();
}
