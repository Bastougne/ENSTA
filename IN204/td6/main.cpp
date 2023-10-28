#include "math.hpp"
#include <iostream>

void test_divide() {
    double i, j;
    for ( ;; ) {
        std::cout << "Le numerateur (0 pour arreter) :";
        std::cin >> i;
        if ( i == 0 ) {
            break;
        }
        std::cout << "Le denominateur :";
        std::cin >> j;
        try {
            double res = divide( i, j );
            std::cout << "Resultat : " << res << std::endl;
        } catch ( division_by_zero ) {
            std::cout << division_by_zero().what() << std::endl;
        }
    }
}

double successive_division( double i ) noexcept( false ) {
    double j;
    std::cout << "Next divisor (-1 to stop sequence): ";
    std::cin >> j;
    if ( j == -1 )
        return i;
    try {
        successive_division( j );
        return divide( i, j );
    } catch ( division_by_zero e ) {
        throw extended_division_by_zero();
    } catch ( extended_division_by_zero e ) {
        e.catched();
        throw e;
    }
}

void test_succesive_division() noexcept {
    double i;
    std::cout << "The numerator: ";
    std::cin >> i;
    try {
        successive_division( i );
    } catch ( extended_division_by_zero e ) {
        e.catched();
        std::cout << "Division by zero occurred after "
                  << e.getCatchNumber()
                  << " divisions" << std::endl;
    }
}

int main() {
    test_succesive_division();
    return ( 0 );
}
