#include <initializer_list>
#include <iostream>

template <class T>
void print_same_type( std::initializer_list<T> il ) {
    auto it = il.begin();
    auto end_it = il.end();
    if ( it != end_it ) {
        std::cout << *it;
        while ( ++it != end_it )
            std::cout << ", " << *it;
        std::cout << std::endl;
    }
}

int print_multiple_types() {
    std::cout << std::endl;
    return ( 0 );
}

template <class T, class... Args>
int print_multiple_types( T first_argument, Args... arguments ) {
    std::cout << first_argument;
    if ( sizeof...( Args ) > 0 ) {
        std::cout << ", ";
    }
    return ( 1 + print_multiple_types( arguments... ) );
}

int main() {
    std::initializer_list<int> list_of_ints = { 1, 3, 2, 4 };
    std::initializer_list<char> list_of_chars = { 'e', 'b' };
    print_same_type( list_of_ints );
    print_same_type( list_of_chars );
    int number_of_args = print_multiple_types( 1, "e", 2.5, 'c' );
    std::cout << number_of_args << std::endl;
    return ( 0 );
}