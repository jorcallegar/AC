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
*										Programa de AC
*	Variables simples:
*		n: tamaño de la imagen
*		tipo_resultado: nos dice si quiere 't' o quiere 'd' 
*		't' es tiempo
*		'd' es datos
*		x: x de la matriz generada
*		y: y de la matriz generada
*		i,k,j: son variables iterativas
*		s: numero de filtros
*		m: dimensiÃ³n de los filtros
*
*	Variables complejas:
*		C[20][5][5]: bateria de filtros
*		B[s][n][n]: Array resultado de la convolución de la imagen
*		R[s][n/2][n/2]: Resultado del pooling
*		M[n/2][n/2]: REsultado del promediado. Salida del algoritmo
*
*/ /*****************************************************************************************/


int main( int argc, char *argv[] )
{
	int n;
	bool tipo_resultado;
	
	/******************
	
	True: Datos
	False: Tiempos
	
	*******************/
	
	
	int x, y, z;						//variables para la matriz
	int k, i, j;						//Variables iteracciones
	
	/*****************
	Parte inicialización del main
	*****************/
	
	if ( argc != 2 ){
		n=120;
		tipo_resultado = false;
	}
	else {
		n = atoi(argv[1]);
		
		if(atoi(argv[2] )== 'd')
			tipo_resultado = true;
		else
			tipo_resultado = false; 
	}

	
	float  A[n][n];
	float C[20][5][5];
	
	int s = 20;
	int m = 5;
	
	float B[s][n][n];
	float R[s][n/2][n/2];
	float M[n/2][n/2];
	
	struct timeval tiempo0, tiempo1;
	
	long time;
	
	
	//////////////////////////////////////////////////
	/*********
	Generacion de matriz
	*********/
	
	
	cout << "----------------------------------------------------       Funciona A       ---------------------"  << endl;
	cout << n;
	for(x=0 ; x<n; x++)
    {
	
    	for(y=0; y<n; y++)
		{
				
    		A[x][y] = (float)((x*y + x + y)) / (((3 *n*n))*(10*10*10));
    		//A[x][y] = A[x][y] / (((3 *n*n))*(10*10*10));
    		//if (x%7==0)
			//	cout << A[x][y]  << endl;
			
    	
		}
	}
	
	system("pause");
	/***********
	Generacion de la bateria de filtros
	Hemos generado  C[k][i][j] que es una bateria de filtros
	************/
	
	gettimeofday(&tiempo0, NULL);
	
	cout << "C" << endl;	
	srand(5);
	for(k=0; k<s;k++){
		for(i=0; i<m;i++){
		
			for(j=0; j<m;j++){
				C[k][i][j]= (rand()*pow(-1,j+k))/RAND_MAX;
				// << C[k][i][j] << endl;
				cout << C[k][i][j] << endl;
			}
		}
	}
	system("pause");
	
    
	/*************
	1.Calculo de la convolucion de la imagen
	
	**************/
	
	cout << "Convolucion B"  << endl;
	for(z=0; z<s ; z++)
	{
 		for(x=2; x<n-2; x++)
 		{
			for(y=2; y<n-2; y++)
			{
				//Lo inicializo a 0, porque cada uno va a tener un valor distinto, los cuales empezarán evidentemete a 0
				B[z][x][y] = 0;						//Cambio -> Añadido
				for(i=-(m/2); i<=(m/2); i++)
            	{
 					for(j=-(m/2); j<=(m/2); j++)
         			{
         				//He añadido el B[z][x][y] en el sumatorio, pues al final todo es una operación de lo va sumando
            	 		B[z][x][y] += A[x+i][y+j] * C[z][((m/2) + i)][((m/2) + j)]; // Cambio (modificación)
            	 		if (x%113==0)
							cout << B[z][x][y]  << endl;
            	 		
					}		  
       			}	   
			}
		}
	}

	
	
	/************
	2.Aplicacion de la funcion no lineal
	***********/
	system("pause");
	
	cout << "Funcion no lineal" << endl;
	for(int z=0; z<s ; z++)
	{
	
		
    	for(x=2; x<n-2; x++)
    	{
        	for(y=2; y<n-2; y++)
        	{
        		//cout << B[z][x][y] << "         ";
            	B[z][x][y]= 1/(1 + 1/pow(2.718281828459045, B[z][x][y]));  
            	if (x%113==0)
            		cout << B[z][x][y]  << endl;
            	//cout << endl;
            	//pause(1);
        	}
    	}
	}

	cout << "Parte Pulling" << endl;
	system("pause");
	/*************
	3.Pooling
	************/
	cout << "*********************************" << endl;
	float max;
	for (z=0; z<s; z++){
		for(x=0; x<n/2; x++){
			for(y=0; y<n/2; y++){
				if(B[z][2*x][2*y] > B[z][2*x][2*y + 1])
					max = B[z][2*x][2*y];
				
				if(max < B[z][2*x+1][2*y])
					max = B[z][2*x+1][2*y];
				
				if(max <  B[z][2*x+1][2*y+1])
					max = B[z][2*x+1][2*y+1];
					
				R[z][x][y] = max;
				if (x%7==113)
					cout << R[z][x][y] << endl;
				
			}
		}
	}
	
	cout << "*********************************" << endl;
	
	cout << "Parte Promedio" << endl;
	system("pause");
	/*************
	4.Promediado
	**************/
	
	float media;

	for (z=0; z<s; z++){
		media=0;
		for(x=0; x<n/2; x++){
			for(y=0; y<n/2; y++){
				//cout << R[z][x][y];
				media += R[z][x][y];

			}
			
		}
		M[x][y]= media/s;
		cout << M[x][y];
		
		cout << endl;
	
	}
	

	
	gettimeofday(&tiempo1, NULL);
	
	time= tiempo1.tv_sec * 1000000-tiempo0.tv_sec * 1000000;
	cout << "El tiempo que tarda es: " << time << endl;
	
	system("PAUSE");
    
    return 0;
}

