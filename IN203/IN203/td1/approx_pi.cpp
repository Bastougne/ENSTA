#include <mpi.h>
#include <stdlib.h>
#include <time.h>

// mpiexec -np nombreThreads --oversubscribe ./a.out nombreFlechettes

int main( int argc, char *argv[] ) {

    int numtasks, rank, r;
    int nbflechettes = atoi( argv[1] );
    MPI_Status status;

    MPI_Init( &argc, &argv ); // Initialisation de MPI
    MPI_Comm globComm; // Défintion d'un communicateur
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang

    srand( time( 0 ) * rank );

    r = 0;
    for ( int i = 0; i < nbflechettes / numtasks; i++ ) {
        float x = (float)rand() / (float)RAND_MAX; // dans le 1er quadrant du cercle
        float y = (float)rand() / (float)RAND_MAX;
        ( x * x + y * y < 1 ) ? r++ : 0;
    }
    if ( rank > 0 ) {
        MPI_Send( &r, 1, MPI_INT, 0, 0, globComm );
    } else {
        int r_tot = r;
        int count = 0;
        while ( count < numtasks - 1 ) {
            MPI_Recv( &r, 1, MPI_INT, MPI_ANY_SOURCE, 0, globComm, &status );
            r_tot += r;
            count++;
        }
        float pi = 4 * (float)r_tot / (float)nbflechettes;
        std::cout << "Après " << numtasks << " lancers de " << nbflechettes / numtasks << " flechettes, on obtient pi ≃ " << pi << std::endl;
    }
    MPI_Finalize();
    return MPI_SUCCESS;
}
