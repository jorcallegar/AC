#include "iostream"
#include "stdlib.h"
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
/*****************************************
Programa de AC
Variables:
n: tamaño de la imagen
entradaTipoDePeticion : nos dice si quiere 't' o quiere 'd' 
't' es tiempo
'd' es datos
x: x de la matriz generada
y: y de la matriz generada
i,k,j: son variables iterativas
s: numero de filtros
m: dimensión de los filtros
C[20][5][5]: bateria de filtros
B[s][n][n]: Array resultado de la convolución de la imagen
R[s][n/2][n/2]: Resultado del pooling
M[n/2][n/2]: REsultado del promediado. Salida del algoritmo
*******************************************/

using namespace std;
int main(int argc, char *argv[])
{
	int n;
	string entradaTipoDePeticion;
	int x, y, k, i, j, z;
	float  A[n][n];
	float C[20][5][5];
	
	int s = 20;
	int m = 5;
	
	float B[s][n][n];
	float R[s][n/2][n/2];
	float M[n/2][n/2];
	
	struct timeval tiempo0, tiempo1;
	
	long time;
	
	if(argc == 2)
		n =120; 
	
	else
		n = atoi(argv[2]);

	
	
	
	
	
	
		
	
	cout << n%2;
	
	/*
	cout <<n;
	if (n % 2 !=0){
		n=120;
		cout << "n es:" + n;
	}**/
	
	//////////////////////////////////////////////////
	/***********************
	Generacion de matriz
	***********************/
	
	
	
	
	
	for(x=0 ; x<n; x+=1)
    {
	
    	for(y=0; y<n; y+=1)
		{
				
    		A[x][y]= ((x*y + x + y) / (3 *n*n))*10^3;
    	
		}
	}
	
	
	/*********************************
	Generacion de la bateria de filtros
	Hemos generado  C[k][i][j] que es una bateria de filtros
	**********************************/
	
	gettimeofday(&tiempo0, NULL);
	
	srand(5);
	for(k=0; k<s;k++){
		for(i=0; i<m;i++){
		
			for(j=0; j<m;j++){
				C[k][i][j]= (rand()*pow(-1,j+k))/RAND_MAX;
			}
		}
	}
	
    
	/***********************************
	1.Calculo de la convolucion de la imagen
	
	**************************************/
	
	
	
	/********************************
	2.Aplicacion de la funcion no lineal
	*********************************/
	

	
	/***********************************
	3.Pooling
	************************************/
	
	int max;
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
			}
		}
	}
	
	
	/***************************************
	4.Promediado
	****************************************/
	
	int media = 0;
	for (z=0; z<s; z++){
		for(x=0; x<n/2; x++){
			for(y=0; y<n/2; y++){
				media += R[z][x][y];
			}
		}
	}
	
	media = media / s;
	
	gettimeofday(&tiempo1, NULL);
	
	time= tiempo1.tv_sec * 1000000-tiempo0.tv_sec * 1000000;
	
	system("PAUSE");
    return 0;
}
