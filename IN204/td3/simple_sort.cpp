#include "simple_sort.hpp"
#include <iostream>
#include <random>
#include <stdlib.h>

namespace monomorphic {

void populate_with_randoms( std::vector<int> &theVector, int theNumberOfValues, int theMinValue, int theMaxValue ) {
    std::random_device rd;
    std::minstd_rand gen( rd() );
    std::uniform_int_distribution<> distribution( theMinValue, theMaxValue );
    theVector.resize( theNumberOfValues );
    for ( int i = 0; i < theNumberOfValues; i++ ) {
        theVector[i] = distribution( gen );
    }
}

void print_vector( const std::vector<int> &anArray ) {
    std::cout << "[";
    for ( unsigned i = 0; i < anArray.size(); i++ ) {
        if ( i > 0 ) {
            std::cout << ", ";
        }
        std::cout << anArray[i];
    }
    std::cout << "]" << std::endl;
}

void simple_sort( std::vector<int> &theValues ) {
    for ( unsigned i = 0; i < theValues.size(); i++ ) {
        for ( unsigned j = i + 1; j < theValues.size(); j++ ) {
            if ( theValues[i] > theValues[j] ) {
                int Temp = theValues[i];
                theValues[i] = theValues[j];
                theValues[j] = Temp;
            }
        }
    }
}
} // namespace monomorphic