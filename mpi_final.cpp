#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "mpi.h"

using namespace std;

/****************************************************************************************/ /*
*
*		Prueba MPI
*	Variables simples:
*		n: tama?o de la imagen
*		tipo_resultado: nos dice si quiere 't' o quiere 'd' 
*		't' es tiempo
*		'd' es datos
*		x: x de la matriz generada
*		y: y de la matriz generada
*		i,k,j: son variables iterativas
*		s: numero de filtros
*		m: dimensión de los filtros
*
*	Variables complejas:
*		C[20][5][5]: bateria de filtros
*		B[s][n][n]: Array resultado de la convoluci?n de la imagen
*		R[s][n/2][n/2]: Resultado del pooling
*		M[n/2][n/2]: REsultado del promediado. Salida del algoritmo
*
*/ /*****************************************************************************************/


#define NUMDAT 4*10 // debe ser divisible por el numero de procesos que use
#define COLECTIVAS // comentar para comunicaciones punto a punto

int main( int args, char *argv[] )
{
	long int n, n_local;
	bool tipo_resultado;
	
	int my_id, num_proc, num_elementos;                    //MPI datos básicos
	/******************
	
	True: Datos
	False: Tiempos
	
	*******************/
	
	
	long int x, y, z;						//variables para la matriz
	long int k, i, j;						//Variables iteracciones
	
	/*****************
	Parte inicializaci?n del main
	*****************/
	
	if (args == 1)
	{
		n = 120;
	}
	else if (args == 2)
	{
		//cout << "EEEhh, colego";
		n = atoi(argv[1]);	
	}

	
	
	float C[20][5][5];
	
	long int s = 20;
	long int m = 5;


	float *A, *A_local;          //A[n][n];
	float *B, *B_local;          //B[s][n][n];
	float *R, *R_local;          //R[s][n/2][n/2];
	float *M, *M_local;          //M[n/2][n/2];
	
	struct timeval tiempo0, tiempo1;
	
	long time;
	
	MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	
	//////////////////////////////////////////////////
	/*********
	Generacion de matriz
	*********/
	
	
	//cout << "----------------------------------------------------      Resultado A 1      ---------------------"  << endl;
	//cout << n;
	
	//Calculamos que todos saben que n_local tienen
	n_local = n / num_proc;
	
	if(my_id == 0)
		n_local += n % num_proc;
	
	//Reservamos memoria para las áreas locales
	A_local = (float *) malloc(n_local*n_local*sizeof(float));
    B_local = (float *) malloc(s*n_local*n_local*sizeof(float));
	B_local = (float *) malloc(s*n_local*n_local/4*sizeof(float));
	M_local = (float *) malloc(n_local*n_local/4*sizeof(float));
	
    if(my_id == 0)
    {
    	A = (float *) malloc(n*n*sizeof(float));
    	B = (float *) malloc(s*n*n*sizeof(float));
    	B = (float *) malloc(s*n*n/4*sizeof(float));
    	M = (float *) malloc(n*n/4*sizeof(float));  
    	
    	//Inicializamos la varibla A
    	for(x=0 ; x<n; x++)
        	for(y=0; y<n; y++)
        		A[x*n +y] = (float)(x*y + x + y) / (3 *n*n)*(1000);
        
        //Inicializamos la CONSTANTE C
        srand(5);
	    for(k = 0; k < s; k++)
    		for(i=0; i < m; i++)
    			for(j=0; j<m;j++)
    				C[k][i][j]= (float)((rand()*pow(-1.0,j+k))/RAND_MAX);
    	
    	//Inicializamos la media y R
    	
    	for(z = 0; z < s; z++)
        {
            for(x = 0; x < n; x++)
            {
                for(y = 0; y < n; y++)
                {
                    B[z*n*n + x*n + y] = 0;
                    
                    if(y < n/2 && x < n/2)
                    {
                        R[z*n*n/4 + x*n/2 + y] = 0;
    					
                        if(z == 0)
                            M[x*n/2 + y] = 0;
                    }
                    
                }
            }
		}
		
		//Solo el rooot necesita controlar el tiempo
        gettimeofday(&tiempo0, NULL);
        
        //La diferencia es que aquí el X_local del root empieza la copia después del resto (n%num_proc)
        MPI_Scatter(&A[n%num_proc], (n*n)/num_proc, MPI_FLOAT, &A_local[n%num_proc], (n*n)/num_proc, MPI_FLOAT, 0, MPI_COMM_WORLD); 
		MPI_Scatter(&B[n%num_proc], (s*n*n)/num_proc, MPI_FLOAT, &B_local[n%num_proc], (s*n*n)/num_proc , MPI_FLOAT, 0, MPI_COMM_WORLD);
    	MPI_Scatter(&R[n%num_proc], (s*n/2*n/2)/num_proc, MPI_FLOAT, &R_local[n%num_proc], (s*n/2*n/2)/num_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);
    	MPI_Scatter(&M[n%num_proc], (n/2*n/2)/num_proc, MPI_FLOAT, &M_local[n%num_proc], (n/2*n/2)/num_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);
    }
    
    else
    {
    	MPI_Scatter(&A[n%num_proc], (n*n)/num_proc, MPI_FLOAT, &A_local[0], (n*n)/num_proc, MPI_FLOAT, 0, MPI_COMM_WORLD); 
		MPI_Scatter(&B[n%num_proc], (s*n*n)/num_proc, MPI_FLOAT, &B_local[0], (s*n*n)/num_proc , MPI_FLOAT, 0, MPI_COMM_WORLD);
    	MPI_Scatter(&R[n%num_proc], (s*n/2*n/2)/num_proc, MPI_FLOAT, &R_local[0], (s*n/2*n/2)/num_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);
    	MPI_Scatter(&M[n%num_proc], (n/2*n/2)/num_proc, MPI_FLOAT, &M_local[0], (n/2*n/2)/num_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}
	
    //Mandamos toca la C, porque todos la necesitan
    MPI_Bcast(C, (s*m*m), MPI_FLOAT, 0, MPI_COMM_WORLD);   		  //Envio de C

    if(my_id == 0)
	{
		//Para el proceso 0, si n no es múltiplo del número de procesadores
    	
		for(int i = 0; i < n%num_proc; i++)
		{
			A_local[i] = A[i];
			B_local[i] = B[i];
			R_local[i] = R[i];
			M_local[i] = M[i];
		}
        
	}
	
	/************
	2.Aplicacion de la funcion no lineal
	***********/
	
	for(z=0; z<s ; z++)
	{
 		for(x=2; x<n_local-2; x++)
 		{
			for(y=2; y<n-2; y++)
			{
				B_local[z*n_local*n + x*n + y] = 0;					
				for(i= -m/2; i <= m/2; i++)
            	{
					for(j= -m/2; j <= m/2; j++)
						B[z*n_local*n + x*n + y] += A[(x+i)*n_local+y+j] * C[z][m/2 + i][m/2 + j];	  
				}	   
			}
		}
	}
    
    
    /*************
	3.Pooling
	************/
	float max = 0;
	for (z=0; z<s; z++)
	{
		for(x=0; x<n_local/2; x++)
		{
			for(y=0; y<n/2; y++)
			{
				if(B_local[z*n_local*n + 2*x*n + 2*y] > B_local[z*n_local*n + 2*x*n + 2*y + 1])
					max = B_local[z*n_local*n + 2*x*n + 2*y];			
				else
					max = B_local[z*n_local*n + 2*x*n + 2*y + 1];	
				
				if(max < B_local[z*n_local*n + (2*x+1)*n + 2*y])
					max = B_local[z*n_local*n + (2*x+1)*n + 2*y];

				if(max <  B_local[z*n_local*n + (2*x+1)*n + 2*y+1])
					max = B_local[z*n_local*n + (2*x+1)*n + 2*y+1];
					
				R_local[z*n_local*n/4 + x*n/2 + y] = max;	
				
			}
		}
	}
	
	/*************
	4.Promediado
	*************/
	
	float media;
	media = 0.0;
	for(x=0; x<n_local/2; x++)
	{
		for(y=0; y<n/2; y++)
		{
			M_local[x*n/2 + y] = 0;
			
			for (z=0; z<s; z++)
				M_local[x*n/2 + y] += R_local[z*n_local*n/4 + x*n/2 + y];
			
			M_local[x*n/2 + y] = (float)(M_local[x*n/2 + y]/s);
		}
	}
	
	//Volvemos a cmabiar el valor de n_local del root por el de los demás
	if(my_id == 0)
		n_local = n / num_proc;
	
	MPI_Gather(M_local, (n_local/2*n/2), MPI_FLOAT, M, (n_local/2*n/2), MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Gather(R_local, s*(n_local/2*n/2), MPI_FLOAT, R, s*(n_local/2*n/2), MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Gather(A_local, (n_local*n), MPI_FLOAT, A, (n_local*n), MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Gather(B_local, (n_local/2*n/2), MPI_FLOAT, M, (n_local/2*n/2), MPI_FLOAT, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD); // Sincronización de barrera
	MPI_Finalize();
	gettimeofday(&tiempo1, NULL);
	
	return 0;	
}
