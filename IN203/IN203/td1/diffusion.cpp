#include <cmath>
#include <mpi.h>
#include <stdlib.h>

// mpiexec -np 2^dimensionHypercube --oversubscribe ./a.out valeurADiffuser
int main( int argc, char *argv[] ) {

    int numtasks, rank, value;
    int next = 0;

    MPI_Status status;
    MPI_Init( &argc, &argv ); // Initialisation de MPI
    MPI_Comm globComm; //Défintion d'un communicateur
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang

    if ( rank == 0 ) {
        value = atoi( argv[1] );
    } else {
        MPI_Recv( &value, 1, MPI_INT, MPI_ANY_SOURCE, 0, globComm, &status );
        std::cout << "Réception de " << value << " par " << rank << std::endl;
    }
    for ( int i = ( rank == 0 ) ? 0 : (int)log2( rank ) + 1; i < (int)log2( numtasks ); i++ ) {
        next = rank + pow( 2, i );
        std::cout << "Envoi de " << value << " à " << next << " par " << rank << std::endl;
        MPI_Send( &value, 1, MPI_INT, next, 0, globComm );
    }
    MPI_Finalize();
    return ( MPI_SUCCESS );
}
