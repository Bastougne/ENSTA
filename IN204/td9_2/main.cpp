#include <chrono>
#include <iostream>
#include <utility>

int factorial( int n ) {
    return ( ( n == 0 ) ? 1 : ( n * factorial( n - 1 ) ) );
}

template <class function, class... Args>
auto estimate_time( function f, Args... arguments ) {
    auto beginning = std::chrono::high_resolution_clock::now();
    auto result = f( arguments... ); // le type de retour n'est pas le type de la fontion !
    auto duration = std::chrono::high_resolution_clock::now() - beginning;
    return ( std::make_pair( duration, result ) );
}

int main() {
    auto pair = std::make_pair( 10, std::chrono::high_resolution_clock::now() );
    auto pair1 = estimate_time( factorial, 100 );
    std::cout << pair.second << std::endl;
    return ( 0 );
}