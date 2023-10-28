#ifndef complexHPP
#define complexHPP
#include <cmath>
#include <iostream>

class Complex {

  public:
    double mRealPart;
    double mImaginaryPart;

    Complex() : mRealPart( 0.0 ), mImaginaryPart( 0.0 ){};

    Complex( double value ) : mRealPart( value ), mImaginaryPart( 0.0 ){};

    Complex( float value ) : mRealPart( value ), mImaginaryPart( 0.0 ){};

    Complex( int value ) : mRealPart( (double)value ), mImaginaryPart( 0.0 ){};

    Complex( double real, double imag ) : mRealPart( real ), mImaginaryPart( imag ){};

    ~Complex(){};

    void print() const {
        std::cout << mRealPart << " + " << mImaginaryPart << "i" << std::endl;
    };

    static Complex polaire( const double rho, const double teta ) {
        return ( Complex( rho * cos( teta ), rho * sin( teta ) ) );
    };
};

template <class charT, class traits = std::char_traits<charT>>
std::basic_ostream<charT, traits> &operator<<( std::basic_ostream<charT, traits> &theStream, const Complex &theComplex ) {
    std::cout << theComplex.mRealPart << " + " << theComplex.mImaginaryPart << "i" << std::endl;
}

#endif
