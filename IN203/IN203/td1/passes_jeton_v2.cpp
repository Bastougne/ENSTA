#include <mpi.h>
#include <stdlib.h>
#include <time.h>

// mpiexec -np nombreThreads --oversubscribe ./a.out

int main( int argc, char *argv[] ) {

    int numtasks, rank;
    int jeton;
    MPI_Status status;

    MPI_Init( &argc, &argv ); // Initialisation de MPI
    MPI_Comm globComm; //Défintion d'un communicateur
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang

    srand( time( 0 ) * rank );

    if ( rank == 0 ) {
        jeton = rand() % 89 + 10;
        std::cout << "création du jeton par la tâche 0 à la valeur " << jeton << " et envoi" << std::endl;
        MPI_Send( &jeton, 1, MPI_INT, 1, 0, globComm );
        MPI_Recv( &jeton, 1, MPI_INT, numtasks - 1, 0, globComm, &status );
        std::cout << "récéption du jeton par la tâche 0 à la valeur " << jeton << std::endl;
    } else {
        MPI_Recv( &jeton, 1, MPI_INT, rank - 1, 0, globComm, &status );
        std::cout << "récéption du jeton par la tâche " << rank << " à la valeur " << jeton << ", incrément à la valeur " << ++jeton;
        jeton = rand() % 89 + 10;
        std::cout << ", modification à la valeur " << jeton << " et envoi" << std::endl;
        MPI_Send( &jeton, 1, MPI_INT, ( rank + 1 ) % numtasks, 0, globComm );
    }
    MPI_Finalize();
    return MPI_SUCCESS;
}
