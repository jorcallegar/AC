#include "iostream"
#include "stdlib.h"

/******************************************

Programa de AC

Variables:
n: tamaño de la imagen
entradaTipoDePeticion : nos dice si quiere 't' o quiere 'd' 
't' es tiempo
'd' es datos
x: x de la matriz generada
y: y de la matriz generada

Hola Soy Ainhoa
*******************************************/

using namespace std;
int main()
{
	int n =120; 
	string entradaTipoDePeticion;
	int x, y;
	float  A[n][n];
		
	if (entradaTipoDePeticion != "t" or entradaTipoDePeticion != "d"){ 
		cout << "Introduce c o d";
		cin >> entradaTipoDePeticion;
	}
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
	
	
	
	
	
	for(x=0 ; x<=n; x+=1)
    {
	
    	for(y=0; y<=n; y+=1)
		{
				
    		A[x][y]= ((x*y + x + y) / (3 *n*n))*10^3;
    	
		}
	}
	
	
	/*********************************
	
	**********************************/
   
    system("PAUSE");
    return 0;
}
