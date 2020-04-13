#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <fstream>

using namespace std;

/****************************************************************************************/ /*
*
*		Prueba MPI
*	Variables simples:
*		n: tama�o de la imagen
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
*		B[s][n][n]: Array resultado de la convoluci�n de la imagen
*		R[s][n/2][n/2]: Resultado del pooling
*		M[n/2][n/2]: REsultado del promediado. Salida del algoritmo
*
*/ /*****************************************************************************************/


int main( int args, char *argv[] )
{
	long int n;
	bool tipo_resultado;
	
	/******************
	
	True: Datos
	False: Tiempos
	
	*******************/
	
	
	long int x, y, z;						//variables para la matriz
	long int k, i, j;						//Variables iteracciones
	
	/*****************
	Parte inicializaci�n del main
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
	
	
	//////////////////////////////////////////////////
	/*********
	Generacion de matriz
	*********/
	
	
	//cout << "----------------------------------------------------      Resultado A 1      ---------------------"  << endl;
	//cout << n;
	for(x=0 ; x<n; x++)
    {
	
    	for(y=0; y<n; y++)
		{
				
    		A[x*n +y] = (float)(x*y + x + y) / (3 *n*n)*(1000);
			
    		
    	
		}
	}
	
	
	//cout << "A[0][0]: " << A[0] << endl;
	//cout << "A[1][1]: " << A[n+1] << endl;
    //cout << "A[2][2]: " << A[2*n+2] << endl;
    //cout << "A[3][3]: " << A[3*n+3] << endl;
	
	//system("pause");
	/***********l
	Generacion de la bateria de filtros
	Hemos generado  C[k][i][j] que es una bateria de filtros
	************/
	
	gettimeofday(&tiempo0, NULL);

	
	//cout << "-----------------------------------	Resultado C 2      ---------------------"  << endl;	
	srand(5);
	for(k = 0; k < s; k++)
	{
		for(i=0; i < m; i++)
		{
		
			for(j=0; j<m;j++)
			{
				C[k][i][j]= (float)((rand()*pow(-1.0,j+k))/RAND_MAX);
				// << C[k][i][j] << endl;
				//cout << C[k][i][j] << "\t";
			
			}
		}
	}
	
	//cout << "C[0][0][0]: " << C[0][0][0] << endl;
	//cout << "C[1][1][1]: " << C[1][1][1] << endl;
    //cout << "C[2][2][2]: " << C[2][2][2] << endl;
    //cout << "C[3][3][3]: " << C[3][3][3] << endl;
	//system("pause");
	
    
	/*************
	1.Calculo de la convolucion de la imagen
	
	**************/
	
    //cout << "-----------------------inicializaci�n de Vectores -------------------------" << endl;
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
					
                    if(z == 0){
                        M[x*n/2 + y] = 0;
						
					}
						

					
                }
                
            }
        }
        
    }
    
    
    
	//cout << "-----------------------------------       Convolucion B  3     ---------------------"  << endl;
	for(z=0; z<s ; z++)
	{
 		for(x=2; x<n-2; x++)
 		{
			for(y=2; y<n-2; y++)
			{
				B[z*n*n + x*n + y] = 0;					
				for(i= -m/2; i <= m/2; i++)
            	{
 					for(j= -m/2; j <= m/2; j++)
         			{
            	 		B[z*n*n + x*n + y] += A[(x+i)*n+y+j] * C[z][m/2 + i][m/2 + j];
						
            	 		
					}		  
       			}	   
			}
		}
	}
	//cout << "B[0][0][0]: " << B[0] << endl;
	//cout << "B[1][1][1]: " << B[n*n + n + 1] << endl;
    //cout << "B[2][2][2]: " << B[2*n*n + 2*n + 2] << endl;
    //cout << "B[3][3][3]: " << B[3*n*n + 3*n + 3] << endl;

	
	
	/************
	2.Aplicacion de la funcion no lineal
	***********/
	//system("pause");	
	
	//cout << "-----------------------------------       Aplicacion lineal B  4     ---------------------" << endl;
	
    float valor = 0;
    for( z=0; z<s ; z++)
	{
	
		
    	for(x=0; x<n; x++)
    	{
        	for(y=0; y<n; y++)
        	{
        		//cout << B[z][x][y] << "         ";
            	//B[z][x][y]= (float)1.0/(1.0 + (float)1.0/(float)pow(2.718281828459045, (float)B[z][x][y]));  
                
                B[z*n*n + x*n + y]=(float)(1.0/(1.0+exp(-B[z*n*n + x*n + y])));
				
            	
            	//cout << endl;
            	//pause(1);
        	}
    	}
	}
	//cout << "B[0][0][0]: " << B[0] << endl;
	//cout << "B[1][1][1]: " << B[n*n + n + 1] << endl;
    //cout << "B[2][2][2]: " << B[2*n*n + 2*n + 2] << endl;
    //cout << "B[3][3][3]: " << B[3*n*n + 3*n + 3] << endl;

	//cout << "Parte Pulling" << endl;
	//system("pause");
	/*************
	3.Pooling
	************/
	//cout << "********************************* Pooling R 5 ************************" << endl;
	float max = 0;
	for (z=0; z<s; z++){
		for(x=0; x<n/2; x++){
			for(y=0; y<n/2; y++){
				
				if(B[z*n*n + 2*x*n + 2*y] > B[z*n*n + 2*x*n + 2*y + 1])//if(B[z][2*x][2*y] > B[z][2*x][2*y + 1])
				{
					max = B[z*n*n + 2*x*n + 2*y];
					
				}
				else
				{
					max = B[z*n*n + 2*x*n + 2*y + 1];
					
				}	
				
				if(max < B[z*n*n + (2*x+1)*n + 2*y])//if(max < B[z][2*x+1][2*y])
				{
					max = B[z*n*n + (2*x+1)*n + 2*y];
					
				}
				if(max <  B[z*n*n + (2*x+1)*n + 2*y+1])
				{
					max = B[z*n*n + (2*x+1)*n + 2*y+1];
					
				}
				R[z*n*n/4 + x*n/2 + y] = max;
				
				
				
			}
		}
	}
	

	
	//cout << "R[0][0][0]: " << R[0] << endl;
	//cout << "R[1][1][1]: " << R[n*n/4 + n/2 +1] << endl;
    //cout << "R[2][2][2]: " << R[2*n*n/4 + 2*n/2 +2] << endl;
    //cout << "R[3][3][3]: " << R[3*n*n/4 + 3*n/2 +3] << endl;
	
	//cout << "********************************* Promediado M 6 ************************" << endl;
	
	
	
	/*************
	4.Promediado
	*************/
	
	float media;

	
	media = 0.0;
	for(x=0; x<n/2; x++)
	{
		for(y=0; y<n/2; y++)
		{
			M[x*n/2 + y] = 0;
			for (z=0; z<s; z++)
			{
			//cout << R[z][x][y];
				M[x*n/2 + y] += R[z*n*n/4 + x*n/2 + y];
				
				if ( x == 0 && y ==0){
					//cout << "----------------------- Valor R ----------------------------" << endl;
					//cout << R[z*n*n/4 + x*n/2 + y];
					
				}
				
			}
			
			
			M[x*n/2 + y] = (float)(M[x*n/2 + y]/s);
				
			if ( x == 0 && y ==0){
					//cout << "------------- Posible problemis------------------------" << endl;
					//cout << M[x*n/2 + y] << endl;
					
				}
		}
			
	}
	//cout << "M[0][0]: " << M[0] << endl;
	//cout << "M[1][1]: " << M[n/2 + 1] << endl;
    //cout << "M[2][2]: " << M[2*n/2 + 2] << endl;
    //cout << "M[3][3]: " << M[3*n/2 + 3] << endl;
	
	
	

	
	gettimeofday(&tiempo1, NULL);
	
	
	time= ((tiempo1.tv_sec*pow(10,6)) +(tiempo1.tv_usec)) - ((tiempo0.tv_sec*pow(10,6)) +(tiempo0.tv_usec))   ;
	cout << time << ";";
	cout <<  n << ",";

	//cout << "Resultados finales ::::::::::::::::"<<endl;
	///system("PAUSE");
    
    //cout << "A[0][0]: " << A[0] << endl;
	//cout << "A[1][1]: " << A[n + 1] << endl;
    //cout << "A[2][2]: " << A[2*n + 2] << endl;
    //cout << "A[3][3]: " << A[3*n + 3] << endl;
    
	//cout << "M[0][0]: " << M[0] << endl;
    //cout << "M[1][1]: " << M[n/2 + 1] << endl; 
	//cout << "M[2][2]: " << M[2*n/2 + 2] << endl;
	//cout << "M[3][3]: " << M[3*n/2 + 3] << endl;
    return 0;
	
}
 

