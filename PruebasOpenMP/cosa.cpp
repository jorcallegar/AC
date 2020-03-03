#include <omp.h> 
#include <stdio.h>

int main (){ 
    int nthreads, thread; 
    #pragma omp parallel private(nthreads, thread)   
    {       
        thread = omp_get_thread_num();     
        nthreads = omp_get_num_threads();     
        printf("Hola soy la hebra = %d de %d \n", thread, nthreads);   
    }   


}