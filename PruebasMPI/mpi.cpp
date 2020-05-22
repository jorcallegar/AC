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
*		m: dimensi�n de los filtros
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
	long int n;
	bool tipo_resultado;
	
	int my_id, num_proc, num_elementos;                    //MPI datos b�sicos
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


	float *A;          //A[n][n];
	float *B;          //B[s][n][n];
	float *R;          //R[s][n/2][n/2];
	float *M;          //M[n/2][n/2];
	
    A = new float[n*n];
    B = new float[s*n*n];
    R = new float[s*n/2*n/2];
    M = new float[n/2*n/2];
	struct timeval tiempo0, tiempo1;
	
	long time;
	
	MPI_Init(&args,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	
	//////////////////////////////////////////////////
	/*********
	Generacion de matriz
	*********/
	
	
	//cout << "----------------------------------------------------      Resultado A 1      ---------------------"  << endl;
	//cout << n;
	
	MPI_Bcast(&n, 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);                      // envio de n
	MPI_Bcast(&s, 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);                      // envio de s
	MPI_Bcast(&m, 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);                      // envio de m
	
    if(my_id == 0)
    {
    	for(x=0 ; x<n; x++)
        {
    	
        	for(y=0; y<n; y++)
    		{
        		A[x*n +y] = (float)(x*y + x + y) / (3 *n*n)*(1000);
    		}
    	}
    	
    	cout << "A[0][0]: " << A[0] << endl;
    	cout << "A[1][1]: " << A[n+1] << endl;
        cout << "A[2][2]: " << A[2*n+2] << endl;
        cout << "A[3][3]: " << A[3*n+3] << endl;
    	
    
	}
}