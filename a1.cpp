#include "iostream"
#include "stdlib.h"

/******************************************

Programa de AC

*******************************************/

using namespace std;
int main()
{

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
