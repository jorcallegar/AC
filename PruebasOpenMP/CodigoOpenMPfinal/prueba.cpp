#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <fstream>
#include <omp.h>


using namespace std;

int main( int args, char *argv[] )
{
    long int n;
    bool tipo_resultado;

    long int x, y, z;                                               //variables para la matriz
    long int k, i, j;                                               //Variables iteracciones

    /*****************
    Parte inicializaciï¿½n del main
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



    float *A;        //A[n][n];
    float C[20][5][5];

    long int s = 20;
    long int m = 5;

    float *B;          //B[s][n][n];
    float *R;          //R[s][n/2][n/2];
    float *M;          //M[n/2][n/2];

    A = new float[n*n];
    B = new float[s*n*n];
    R = new float[s*n/2*n/2];
    M = new float[n/2*n/2];
    struct timeval tiempo0, tiempo1;

    long time;


    for(x=0 ; x<n; x++)
    {

        for(y=0; y<n; y++)
        {
            A[x*n +y] = (float)(x*y + x + y) / (3 *n*n)*(1000);
        }
    }

    srand(5);
    for(k = 0; k < s; k++)
    {
        for(i=0; i < m; i++)
        {

            for(j=0; j<m;j++)
            {
                    C[k][i][j]= (float)((rand()*pow(-1.0,j+k))/RAND_MAX);
            }
        }
    }


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
                    {
                        M[x*n/2 + y] = 0;
                                            
                    }
                }

            }
        }

    }


    ///******************************************************///

    gettimeofday(&tiempo0, NULL);
        //cout << "-----------------------------------       Convolucion B  3     ---------------------"  << endl;
    #pragma omp parallel for private (i, j)  collapse(3) schedule(dynamic) //z, x,
    for(z=0; z<s ; z++)
    {
        for(x=2; x<n-2; x++)
        {
            for(y=2; y<n-2; y++)
            {
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

    cout << "B[0][0][0]: " << B[0] << endl;
    cout << "B[1][1][1]: " << B[n*n + n + 1] << endl;
    cout << "B[2][2][2]: " << B[2*n*n + 2*n + 2] << endl;
    cout << "B[3][3][3]: " << B[3*n*n + 3*n + 3] << endl;

    gettimeofday(&tiempo1, NULL);


    time= ((tiempo1.tv_sec*pow(10,6)) +(tiempo1.tv_usec)) - ((tiempo0.tv_sec*pow(10,6)) +(tiempo0.tv_usec))   ;
    cout << time << ";";
}
