// Produit matrice-vecteur
#include <cassert>
#include <iostream>
#include <mpi.h>
#include <vector>

class Matrix : public std::vector<double> {
  public:
    int m_nrows, m_ncols;

    Matrix( int dim );
    Matrix( int nrows, int ncols );
    Matrix( int dim, int rank, int numtasks );
    Matrix( const Matrix &A ) = delete;
    Matrix( Matrix &&A ) = default;
    ~Matrix() = default;

    Matrix &operator=( const Matrix &A ) = delete;
    Matrix &operator=( Matrix &&A ) = default;

    double &operator()( int i, int j ) { return m_arr_coefs[i + j * m_nrows]; }
    double operator()( int i, int j ) const { return m_arr_coefs[i + j * m_nrows]; }

    std::vector<double> operator*( const std::vector<double> &u ) const;

    std::ostream &print( std::ostream &out ) const {
        const Matrix &A = *this;
        out << "[\n";
        for ( int i = 0; i < m_nrows; ++i ) {
            out << " [ ";
            for ( int j = 0; j < m_ncols; ++j ) {
                out << A( i, j ) << " ";
            }
            out << " ]\n";
        }
        out << "]";
        return out;
    }

  private:
    std::vector<double> m_arr_coefs;
};

inline std::ostream &operator<<( std::ostream &out, const Matrix &A ) { return A.print( out ); }

inline std::ostream &operator<<( std::ostream &out, const std::vector<double> &u ) {
    out << "[ ";
    for ( const auto &x : u )
        out << x << " ";
    out << " ]";
    return out;
}

std::vector<double> Matrix::operator*( const std::vector<double> &u ) const {
    const Matrix &A = *this;
    assert( u.size() == unsigned( m_ncols ) );
    std::vector<double> v( m_nrows, 0. );
    for ( int i = 0; i < m_nrows; ++i ) {
        for ( int j = 0; j < m_ncols; ++j ) {
            v[i] += A( i, j ) * u[j];
        }
    }
    return v;
}

Matrix::Matrix( int dim ) : m_nrows( dim ), m_ncols( dim ), m_arr_coefs( dim * dim ) {
    for ( int i = 0; i < dim; ++i ) {
        for ( int j = 0; j < dim; ++j ) {
            ( *this )( i, j ) = ( i + j ) % dim;
        }
    }
}

Matrix::Matrix( int nrows, int ncols ) : m_nrows( nrows ), m_ncols( ncols ), m_arr_coefs( nrows * ncols ) {
    int dim = ( nrows > ncols ? nrows : ncols );
    for ( int i = 0; i < nrows; ++i ) {
        for ( int j = 0; j < ncols; ++j ) {
            ( *this )( i, j ) = ( i + j ) % dim;
        }
    }
}

Matrix::Matrix( int dim, int rank, int numtasks ) : m_nrows( dim ), m_ncols( dim / numtasks ), m_arr_coefs( dim * dim ) {
    int debut = rank * ( dim / numtasks );
    int fin = ( rank + 1 ) * ( dim / numtasks );
    for ( int i = 0; i < dim; ++i ) { // lignes
        for ( int j = debut; j < fin; ++j ) { // colonnes
            ( *this )( i, j - debut ) = ( i + j ) % dim;
        }
    }
}

int main( int argc, char *argv[] ) { // Parallélisation par colonnes                                            (   )           (   )
    MPI_Init( &argc, &argv ); // Initialisation de MPI                                                          (   )           (   )
    //                                                                                                          ( i ) * ( i ) = (   )
    int rank, numtasks; //                                                                                      (   )           (   )
    MPI_Comm globComm; // Défintion d'un communicateur                                                          (   )           (   )
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang

    const int N = 120;
    Matrix A( N, rank, numtasks );
    //std::cout << "A : " << A << std::endl;
    std::vector<double> u( N / numtasks );
    for ( int i = 0; i < N / numtasks; ++i ) {
        u[i] = i + 1 + rank * ( N / numtasks );
    }
    //std::cout << " u : " << u << std::endl;
    std::vector<double> v = A * u; // chaque v[i]_process_rank contient une valeur dont la somme vaut v[i]
    std::vector<double> v2( N );
    MPI_Allreduce( v.data(), v2.data(), v.size(), MPI_DOUBLE, MPI_SUM, globComm );
    std::cout << "A.u = " << v2 << std::endl;

    MPI_Finalize();
    return EXIT_SUCCESS;
}