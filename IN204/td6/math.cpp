#include "math.hpp"
#include <iostream>

double divide( double a, double b ) {
    if ( !b )
        throw division_by_zero();
    return ( a / b );
}
