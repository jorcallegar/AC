#include "iostream"
#include "stdlib.h"

/******************************************

Programa de AC

Variables:
n: tamaño de la imagen
entradaTipoDePeticion : nos dice si quiere t o quiere d 
't' es tiempo
'd' es datos



*******************************************/

using namespace std;
int main()
{
	int n; 
	string entradaTipoDePeticion;
		
	if (entradaTipoDePeticion != "t" or entradaTipoDePeticion != "d"){ 
		cout << "Introduce c o d";
		cin >> entradaTipoDePeticion;
	}

	
	for(int i=50;i<=100;i+=2)
    {
	
    	for(int j=0; j<=100;j+=2)
		{
				
    		for(int k=0; k<=100;k+=2)
			{
				cout << (float)rand()/RAND_MAX;
				cout << "  ";
			}
		}
	}
   
    system("PAUSE");
    return 0;
}
