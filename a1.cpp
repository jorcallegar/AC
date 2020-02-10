#include "iostream"
#include "stdlib.h"
#include <time.h>       /* time */
#include <math.h>
#include <string.h>
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
	
	if(argc == 2)
		n =120; 
	
	else
		n = atoi(argv[2]);

	
	string entradaTipoDePeticion;
	int x, y, k, i, j;
	float  A[n][n];
	float C[20][5][5];
	
	int s = 20;
	int m = 5;
	
	float B[s][n][n];
	float R[s][n/2][n/2];
	float M[n/2][n/2];
	
	
	
		
	
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
	
	system("pause");
	/*********************************
	Generacion de la bateria de filtros
	Hemos generado  C[k][i][j] que es una bateria de filtros
	**********************************/
	
	srand(5);
	for(k=0; k<s;k++){
		for(i=0; i<m;i++){
		
			for(j=0; j<m;j++){
				C[k][i][j]= (rand()*pow(-1,j+k))/RAND_MAX;
			}
		}
	}
    
	/***********************************
	1.Cálculo de la convolución de la imagen
	
	**************************************/
	
	
	/********************************
	2.Aplicacion de la funcion no lineal
	*********************************/
	
	
	/***********************************
	3.Pooling
	************************************/
	
	/***************************************
	4.Promediado
	****************************************/
	
	
	
	
	system("PAUSE");
    return 0;
}
