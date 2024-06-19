#include <stdio.h>
#include <mpi.h>
int main (int argc, char *argv[]){
	int proc, cant, N, i, j;
  
	printf("Introduzca N: ");
    scanf("%d", &N);
    int matriz[N][N];
    int vector[N];
    int res[N];
    
    printf("Introduzca la matriz de %dx%d:\n",N,N);
	for(i = 0; i < N; i++){
		for (j = 0; j < N; j++) {
			int x;
			scanf("%d", &x);
			matriz[i][j] = x;
		}
	}
    
    printf("Introduzca el vector de dimension %d:\n",N);
	for(i = 0; i < N; i++){
		int x;
		scanf("%d", &x);
		vector[i] = x;
	}
  
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc);
	MPI_Comm_size(MPI_COMM_WORLD, &cant);
	
	for (i = 0; i < N; i++) {
	    int temp = 0;
	    for (j = 0; j < N; j++) {
	        temp += matriz[i][j] * vector[j];
	    }
	    res[i] = temp;
	}
	
	if(proc==0){
		printf("\nResultado:\n");
		for (int i = 0; i < N; i++) {
		    printf("%d ", res[i]);
		}
  }
    
	MPI_Finalize();
}
