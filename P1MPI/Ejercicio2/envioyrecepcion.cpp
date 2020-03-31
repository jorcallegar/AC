#include <mpi.h> 
#include <stdio.h>
int main(int argc, char *argv[]) 
{     
	int rank, contador;     
	MPI_Status estado;    
	MPI_Init(&argc, &argv); // Inicio la comunicacion de procesos    
 	MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Obtiene valor id propio     
	//Envia y recibe mensajes     
	MPI_Send(&rank //referencia al elemento a enviar             
		,1 // tamaño del vector a enviar             
		,MPI_INT // Tipo de dato que se envia             
		,rank // id del proceso destino             
		,0 //etiqueta             
		,MPI_COMM_WORLD); //Comunicador por el que se manda 
		,MPI_Recv(&contador // Referencia donde se almacena lo recibido             
		,1 // tamaño del vector a recibir             
		,MPI_INT // Tipo de dato que recibe             
		,rank // id del proceso origen del que se recibe             
		,0 // etiqueta
		,MPI_COMM_WORLD // Comunicador por el que se recibe             
		,&estado); // estructura informativa del estatus     
	printf("Soy el proceso %d y he recibido %d\n",rank,contador);     		MPI_Finalize();     
	return 0; 
}
