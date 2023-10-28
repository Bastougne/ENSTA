#include <mpi.h>
#include <stdlib.h>

// mpiexec -np nombreThreads --oversubscribe ./a.out jetonInitial

int main( int argc, char *argv[] ) {

    int numtasks, rank;
    int jeton;
    MPI_Status status;

    MPI_Init( &argc, &argv ); // Initialisation de MPI
    MPI_Comm globComm; //Défintion d'un communicateur
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang

    if ( rank == 0 ) {
        jeton = atoi( argv[1] );
        std::cout << "création du jeton par la tâche 0 à la valeur " << jeton << " et envoi" << std::endl;
        MPI_Send( &jeton, 1, MPI_INT, 1, 0, globComm );
        MPI_Recv( &jeton, 1, MPI_INT, numtasks - 1, 0, globComm, &status );
        std::cout << "récéption du jeton par la tâche 0 à la valeur " << jeton << std::endl;
    } else {
        MPI_Recv( &jeton, 1, MPI_INT, rank - 1, 0, globComm, &status );
        std::cout << "récéption du jeton par la tâche " << rank << " à la valeur " << jeton << ", incrément et envoi" << std::endl;
        jeton++;
        MPI_Send( &jeton, 1, MPI_INT, ( rank + 1 ) % numtasks, 0, globComm );
    }
    MPI_Finalize();
    return MPI_SUCCESS;
}
