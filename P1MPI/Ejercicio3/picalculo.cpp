#include <mpi.h> 
#include <stdlib.h> // Incluido para el uso de atoi 
#include <stdio.h> 
int main(int argc, char *argv[])  
{    
	// Cálculo de PI   
	int n; 
	printf("Introduce la precisión del cálculo (n > 0): "); 
	scanf("%d",&n); 
	fflush(stdout);   
	double PI25D = 3.141592653589793238462643;   
	double h = 1.0 / (double) n;   
	double sum = 0.0;   
	for (int i = 0; i < n; i++) { 
		double x = h * ((double)i + 0.5);
		sum += (4.0 / (1.0 + x*x));   
	}   
	double pi = sum * h;     
	printf ("El valor aproximado de PI es: %f, con un error de %f \n",pi,fabs(pi - PI25D));   
	return 0; 
} 
