/* seq_dot.c – calcula un producto escalar de forma secuencial. 
*  
* Input:  
*     n: talla de los vectores  
*  x, y: los vectores  
*  
* Output:  
*     el producto escalar de x por y. 
*  Nota:  en  la  versión  paralela  n  es  múltiplo  del  número  de  procesadores  
*/ 
#include <stdio.h> 
#include <math.h> 
#include <sys/time.h> 
#include <time.h> 
#include <stdlib.h> 
#include "mpi.h" 
#define MAXN 80000000 
#define TUNIT 1.0e+6 

main(int argc, char* argv[]) 
{   
	double *x, *y;  
	double dot, local_dot;   
	int    i, n;   
	double start, finish, dt1;   
	struct timeval tv1, tv2;   
	clock_t tstart,tend;   
	double cpu_time_used;   
	MPI_Init(&argc, &argv); 
	if (argc<2){    
		printf("Entra el número de elementos de cada vector: \n");     			scanf("%d", &n);   
	}
	else     
		n=atoi(argv[1]);   

	// Reserva de espacio para los vectores     
	x = (double *) calloc(n, sizeof(double));     
	y = (double *) calloc(n, sizeof(double));   
	// Inicio de los vectores a 1     
	for (i=0; i<n; i++) {x[i] = 1.0; y[i] = 1.0;} 
	
	//Toma de tiempos iniciales     
	tstart = clock();     
	gettimeofday(&tv1, (struct timezone*)0);     
	start = MPI_Wtime(); 
	/******* calcula el product escalar */   
	dot = 0.0;   
	for (i = 0; i < n; i++)     
		dot += x[i] * y[i];  
	free(x); free(y); 
	//Toma de tiempos finales     
	tend = clock();     
	gettimeofday(&tv2, (struct timezone*)0);     
	finish = MPI_Wtime();   
	dt1=  (tv2.tv_sec  -  tv1.tv_sec)  *  1000000.0  +  (tv2.tv_usec  -tv1.tv_usec);   
	cpu_time_used = ((double)(tend-tstart))/CLOCKS_PER_SEC;     

	printf("El product escalar es %f \n\n", dot);     
	printf("Tiempo de cpu (CLOCK) : %12.5f secs\n",cpu_time_used);     		printf("Tiemp  o (gettimeofday) = %12.5f secs\n",dt1/TUNIT);     		printf("Tiempo (MPI_WTime) = %12.5f secs\n",finish-start);
   	MPI_Finalize(); 
}  /* main */ 


