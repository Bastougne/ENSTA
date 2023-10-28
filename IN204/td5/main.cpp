#include "complex.hpp"
#include <iostream>

const Complex I( 0.0, 1.0 );

int main() {
    Complex c( 3.0, 2.0 );
    c = Complex::polaire( 1.0, 3.14159 / 2 );
    std::cout << c << std::endl;
    return ( 0 );
}
