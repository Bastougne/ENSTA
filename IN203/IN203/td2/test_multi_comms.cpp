#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[] ) {
    int rank, new_rank, sendbuf, recvbuf, numtasks;
    MPI_Comm new_comm; // required variable
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numtasks );
    if ( rank % 2 == 0 ) {
        MPI_Comm_split( MPI_COMM_WORLD, 0, rank, &new_comm );
    } else {
        MPI_Comm_split( MPI_COMM_WORLD, 1, rank, &new_comm );
    }
    sendbuf = rank;
    MPI_Allreduce( &sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, new_comm );
    MPI_Comm_rank( new_comm, &new_rank ); // get rank in new communicator
    printf( "rank = %d, new_rank = %d, recvbuf = %d\n", rank, new_rank, recvbuf );
    MPI_Finalize();
    return ( 0 );
}