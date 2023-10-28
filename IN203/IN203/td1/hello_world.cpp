#include <mpi.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {

    int numtasks, rank;
    MPI_Init( &argc, &argv ); // Initialisation de MPI
    MPI_Comm globComm; //Défintion d'un communicateur
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang

    std::cout << "Bounjour, je suis la tâche n°" << rank << " sur " << numtasks << " tâches." << std::endl;

    MPI_Finalize();
    return MPI_SUCCESS;
}
