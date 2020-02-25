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
	
	
	cout << "----------------------------------------------------      Resultado A 1      ---------------------"  << endl;
	cout << n;
	for(x=0 ; x<n; x++)
    {
	
    	for(y=0; y<n; y++)
		{
				
    		A[x][y] = (float)(x*y + x + y) / (3 *n*n)*(1000);
    		
    	
		}
	}
	
	cout << "A[0][0]: " << A[0][0] << endl;
	cout << "A[1][1]: " << A[1][1] << endl;
    cout << "A[2][2]: " << A[2][2] << endl;
    cout << "A[3][3]: " << A[3][3] << endl;
	
	system("pause");
	/***********
	Generacion de la bateria de filtros
	Hemos generado  C[k][i][j] que es una bateria de filtros
	************/
	
	gettimeofday(&tiempo0, NULL);
	
	cout << "-----------------------------------	Resultado C 2      ---------------------"  << endl;	
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
	
	cout << "C[0][0][0]: " << C[0][0][0] << endl;
	cout << "C[1][1][1]: " << C[1][1][1] << endl;
    cout << "C[2][2][2]: " << C[2][2][2] << endl;
    cout << "C[3][3][3]: " << C[3][3][3] << endl;
	system("pause");
	
    
	/*************
	1.Calculo de la convolucion de la imagen
	
	**************/
	
	cout << "-----------------------------------       Convolucion B  3     ---------------------"  << endl;
	for(z=0; z<s ; z++)
	{
 		for(x=2; x<n-2; x++)
 		{
			for(y=2; y<n-2; y++)
			{
				//Lo inicializo a 0, porque cada uno va a tener un valor distinto, los cuales empezarán evidentemete a 0
				B[z][x][y] = 0;						//Cambio -> Añadido
				for(i= -m/2; i <= m/2; i++)
            	{
 					for(j= -m/2; j <= m/2; j++)
         			{
         				//He añadido el B[z][x][y] en el sumatorio, pues al final todo es una operación de lo va sumando
            	 		B[z][x][y] += A[x+i][y+j] * C[z][m/2 + i][m/2 + j];
            	 		
					}		  
       			}	   
			}
		}
	}
	cout << "B[0][0][0]: " << B[0][0][0] << endl;
	cout << "B[1][1][1]: " << B[1][1][1] << endl;
    cout << "B[2][2][2]: " << B[2][2][2] << endl;
    cout << "B[3][3][3]: " << B[3][3][3] << endl;

	
	
	/************
	2.Aplicacion de la funcion no lineal
	***********/
	system("pause");
	
	cout << "-----------------------------------       Aplicacion lineal B  4     ---------------------" << endl;
	for(int z=0; z<s ; z++)
	{
	
		
    	for(x=2; x<n-2; x++)
    	{
        	for(y=2; y<n-2; y++)
        	{
        		//cout << B[z][x][y] << "         ";
            	//B[z][x][y]= (float)1.0/(1.0 + (float)1.0/(float)pow(2.718281828459045, (float)B[z][x][y]));  
            	B[z][x][y]=(float)(1.0/(1.0+exp(-B[z][x][y])));
            	
            	
            	//cout << endl;
            	//pause(1);
        	}
    	}
	}
	cout << "B[0][0][0]: " << B[0][0][0] << endl;
	cout << "B[1][1][1]: " << B[1][1][1] << endl;
    cout << "B[2][2][2]: " << B[2][2][2] << endl;
    cout << "B[3][3][3]: " << B[3][3][3] << endl;

	cout << "Parte Pulling" << endl;
	system("pause");
	/*************
	3.Pooling
	************/
	cout << "********************************* Pooling R 5 ************************" << endl;
	float max = 0;
	for (z=0; z<s; z++){
		for(x=2; x<n/2+2; x++){
			for(y=2; y<n/2+2; y++){
				
				if(B[z][2*x][2*y] > B[z][2*x][2*y + 1])
					max = B[z][2*x][2*y];
				else
					max = B[z][2*x][2*y + 1];
					
				if(max < B[z][2*x+1][2*y])
					max = B[z][2*x+1][2*y];
				
				if(max <  B[z][2*x+1][2*y+1])
					max = B[z][2*x+1][2*y+1];
					
				R[z][x-2][y-2] = max;
				
				
				
			}
		}
	}
	

	
	cout << "R[0][0][0]: " << R[0][0][0] << endl;
	cout << "R[1][1][1]: " << R[1][1][1] << endl;
    cout << "R[2][2][2]: " << R[2][2][2] << endl;
    cout << "R[3][3][3]: " << R[3][3][3] << endl;
	
	cout << "********************************* Promediado M 6 ************************" << endl;
	
	
	system("pause");
	/*************
	4.Promediado
	*************/
	
	float media;

	
	media = 0.0;
	for(x=0; x<n/2; x++)
	{
		for(y=0; y<n/2; y++)
		{
			M[x][y] = 0;
			for (z=0; z<s; z++)
			{
			//cout << R[z][x][y];
				M[x][y] += R[z][x][y];
				if ( x == 0 && y ==0){
					cout << "----------------------- Valor R ----------------------------" << endl;
					cout << R[z][x][y];
				}
				
			}
			
			
			M[x][y] = (float)(M[x][y]/s);
			if ( x == 0 && y ==0){
					cout << "------------- Posible problemis------------------------" << endl;
					cout << M[x][y] << endl;
				}
		}
			
	}
	cout << "M[0][0]: " << M[0][0] << endl;
	cout << "M[1][1]: " << M[1][1] << endl;
    cout << "M[2][2]: " << M[2][2] << endl;
    cout << "M[3][3]: " << M[3][3] << endl;
	
	
	

	
	gettimeofday(&tiempo1, NULL);
	
	time= tiempo1.tv_sec -tiempo0.tv_sec ;
	cout << "El tiempo que tarda es: " << time << endl;
	cout << "Resultados finales ::::::::::::::::"<<endl;
	system("PAUSE");
    
    cout << "A[0][0]: " << A[0][0] << endl;
	cout << "A[1][1]: " << A[1][1] << endl;
    cout << "A[2][2]: " << A[2][2] << endl;
    cout << "A[3][3]: " << A[3][3] << endl;
    
	cout << "M[0][0]: " << M[0][0] << endl;
    cout << "M[1][1]: " << M[1][1] << endl; 
	cout << "M[2][2]: " << M[2][2] << endl;
	cout << "M[3][3]: " << M[3][3] << endl;

    return 0;
}
