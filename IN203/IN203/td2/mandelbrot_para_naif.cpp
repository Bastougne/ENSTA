#include <assert.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <string>
#include <vector>

struct Complex {
    double real, imag;

    Complex() {
        real = 0;
        imag = 0;
    }

    Complex( double r, double i ) {
        real = r;
        imag = i;
    }

    Complex operator+( const Complex &z ) {
        return ( Complex( real + z.real, imag + z.imag ) );
    }

    Complex operator*( const Complex &z ) {
        return ( Complex( real * z.real - imag * z.imag, real * z.imag + imag * z.real ) );
    }

    double sqNorm() {
        return real * real + imag * imag;
    }
};

std::ostream &operator<<( std::ostream &os, const Complex &c ) {
    os << "(" << c.real << "," << c.imag << ")" << std::endl;
    return ( os );
}

int iterMandelbrot( int maxIter, const Complex &c ) {
    Complex z( 0., 0. );
    // On vérifie dans un premier temps si le complexe
    // n'appartient pas à une zone de convergence connue :
    // Appartenance aux disques  C0{(0,0),1/4} et C1{(-1,0),1/4}
    if ( c.real * c.real + c.imag * c.imag < 0.0625 ) {
        return maxIter;
    }
    if ( ( c.real + 1 ) * ( c.real + 1 ) + c.imag * c.imag < 0.0625 ) {
        return maxIter;
    }
    // Appartenance à la cardioïde {(1/4,0),1/2(1-cos(theta))}
    if ( ( c.real > -0.75 ) && ( c.real < 0.5 ) ) {
        Complex ct( c.real - 0.25, c.imag );
        double ctnrm2 = sqrt( ct.sqNorm() );
        if ( ctnrm2 < 0.5 * ( 1. - ct.real / ctnrm2 ) ) {
            return maxIter;
        }
    }
    int niter = 0;
    while ( ( z.sqNorm() < 4 ) && ( niter < maxIter ) ) {
        z = z * z + c;
        niter++;
    }
    return ( niter );
}

void computeMandelbrotSetRow( int W, int H, int maxIter, int num_ligne, int *pixels ) {
    // Calcul le facteur d'échelle pour rester dans le disque C0{(0,0),2}
    double scaleX = 3. / ( W - 1. );
    double scaleY = 2.25 / ( H - 1. );
    // On parcourt les pixels de l'espace image :
    for ( int j = 0; j < W; j++ ) {
        Complex c( j * scaleX - 2, num_ligne * scaleY - 1.125 );
        pixels[j] = iterMandelbrot( maxIter, c );
    }
}

std::vector<int> computeMandelbrotSet( int W, int H, int maxIter, int debut, int fin ) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<int> pixels( W * ( fin - debut ) );
    start = std::chrono::system_clock::now();
    // On parcourt les pixels de l'espace image :
    for ( int i = debut; i < fin; i++ ) {
        computeMandelbrotSetRow( W, H, maxIter, i, pixels.data() + W * ( fin - i - 1 ) );
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Temps calcul lignes " << debut << " à " << fin << " ensemble mandelbrot : " << elapsed_seconds.count() << std::endl;
    return ( pixels );
}

/** Construit et sauvegarde l'image finale **/
void savePicture( const std::string &filename, int W, int H, const std::vector<int> &nbIters, int maxIter ) {
    double scaleCol = 1. / maxIter; // 16777216
    std::ofstream ofs( filename.c_str(), std::ios::out | std::ios::binary );
    ofs << "P6\n"
        << W << " " << H << "\n255\n";
    for ( int i = 0; i < W * H; i++ ) {
        double iter = scaleCol * nbIters[i];
        unsigned char r = (unsigned char)( 256 - ( (unsigned)( iter * 256 ) & 0xFF ) );
        unsigned char b = (unsigned char)( 256 - ( (unsigned)( iter * 65536 ) & 0xFF ) );
        unsigned char g = (unsigned char)( 256 - ( (unsigned)( iter * 16777216 ) & 0xFF ) );
        ofs << r << g << b;
    }
    ofs.close();
}

int main( int argc, char *argv[] ) {
    const int W = 800;
    const int H = 600;
    const int maxIter = 8 * 65536;
    //const int maxIter = 16777216;

    int rank, numtasks;
    MPI_Status status;
    MPI_Init( &argc, &argv ); // Initialisation de MPI
    MPI_Comm globComm; // Défintion d'un communicateur
    MPI_Comm_dup( MPI_COMM_WORLD, &globComm );
    MPI_Comm_size( globComm, &numtasks ); // Lit le nombre de tâches
    MPI_Comm_rank( globComm, &rank ); // Lit mon rang
    assert( H % numtasks == 0 ); // on veut éviter les effets de bord
    std::cout << "hey process " << rank << " : ";
    int debut = rank * ( H / numtasks );
    int fin = ( rank + 1 ) * ( H / numtasks );
    if ( rank > 0 ) { // ces processus calculent leur partie de l'ensemble et la renvoient au processus 0
        auto iters = computeMandelbrotSet( W, H, maxIter, debut, fin );
        MPI_Send( iters.data(), iters.size(), MPI_INT, 0, 0, globComm );
    } else {
        // on push back dans l'ordre inverse de calcul donc on enregistre le calcul de 0 dans une autre variable
        auto iters_0 = computeMandelbrotSet( W, H, maxIter, debut, fin );
        std::vector<int> iters_tot;
        std::vector<int> iters( iters_0.size() );
        for ( int i = numtasks - 1; i >= 0; i-- ) {
            if ( i > 0 ) {
                MPI_Recv( iters.data(), iters.size(), MPI_INT, i, 0, globComm, &status );
                for ( int j = 0; j < iters.size(); j++ ) {
                    iters_tot.push_back( iters[j] ); // push back du tableau partiel dans le tableau total
                }
            } else {
                for ( int j = 0; j < iters.size(); j++ ) {
                    iters_tot.push_back( iters_0[j] );
                }
            }
        }
        savePicture( "mandelbrot.tga", W, H, iters_tot, maxIter );
    }
    MPI_Finalize();
    return ( MPI_SUCCESS );
}
