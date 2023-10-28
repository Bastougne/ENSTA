#include <iostream>
#include <vector>

void insertion_sort( std::vector<int> &anArray ) {
    for ( int i = 0; i < anArray.size(); i++ ) {
        for ( int j = i + 1; j < anArray.size(); j++ ) {
            if ( anArray[i] > anArray[j] )
                std::swap( anArray[i], anArray[j] );
        }
    }
}

void print( std::vector<Base *> anArray ) {
    std::cout << "[";
    int lastIndex = anArray.size() - 1;
    if ( lastIndex >= 0 ) {
        for ( int i = 0; i < lastIndex; i++ ) {
            anArray[i]->print();
            std::cout << ", ";
        }
        anArray[lastIndex]->print();
    }
    std::cout << "]";
}
