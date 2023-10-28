#include "counter.hpp"

void testNext( BaseCounter &aCounter ) {
    for ( int i = 0; i < 10; i++ ) {
        aCounter.next();
        std::cout << aCounter << std::endl;
    }
};