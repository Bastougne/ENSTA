#include "simple_sort.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    using namespace polymorphic;

    std::vector<int> values;
    populate_with_randoms( values, 10, 20, 40 );
    print_vector( values );
    simple_sort( values );
    print_vector( values );

    std::vector<char> charValues;
    populate_with_randoms( charValues, 10, 'A', 'Z' );
    print_vector<char>( charValues );
    simple_sort( charValues );
    print_vector( charValues );

    std::vector<float> floatValues;
    populate_with_randoms( floatValues, 10, 20.0, 40.0 );
    print_vector( floatValues );
    simple_sort( floatValues );
    print_vector( floatValues );
}