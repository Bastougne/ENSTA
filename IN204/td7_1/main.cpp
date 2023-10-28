#include "counter.hpp"

int main() {
    ForwardCounter forward( 10 );
    BackwardCounter backward( 7 );
    testNext( forward );
    testNext( backward );
}