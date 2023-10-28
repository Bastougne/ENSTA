#ifndef simple_sort_hpp
#define simple_sort_hpp

#include <iostream>
#include <random>
#include <vector>


namespace monomorphic {

void populate_with_randoms( std::vector<int> &theVector, int theNumberOfValues, int theMinValue, int theMaxValue );

void print_vector( const std::vector<int> &anArray );

void simple_sort( std::vector<int> &theValues );

} // namespace monomorphic

namespace polymorphic {

template <class T, class genType>
void populate_with_randoms( std::vector<T> &theVector, int theNumberOfValues, genType theMinValue, genType theMaxValue ) {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_real_distribution<> distribution( theMinValue, theMaxValue );
    theVector.resize( theNumberOfValues );
    for ( int i = 0; i < theNumberOfValues; i++ ) {
        theVector[i] = (T)distribution( gen );
    }
}

template <class T>
void print_vector( const std::vector<T> &anArray ) {
    std::cout << "[";
    for ( unsigned i = 0; i < anArray.size(); i++ ) {
        if ( i > 0 ) {
            std::cout << ", ";
        }
        std::cout << anArray[i];
    }
    std::cout << "]" << std::endl;
}

template <class T>
void simple_sort( std::vector<T> &theValues ) {
    for ( unsigned i = 0; i < theValues.size(); i++ ) {
        for ( unsigned j = i + 1; j < theValues.size(); j++ ) {
            if ( theValues[i] > theValues[j] ) {
                T Temp = theValues[i];
                theValues[i] = theValues[j];
                theValues[j] = Temp;
            }
        }
    }
}

} // namespace polymorphic

#endif