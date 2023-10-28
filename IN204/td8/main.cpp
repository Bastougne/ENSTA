#include <future>
#include <iostream>
#include <sstream>
#include <thread>

std::string computeE( int numberOfDigits ) {
    int sizeOfTable = numberOfDigits + 9;
    int *table = (int *)_malloca( sizeOfTable * sizeof( numberOfDigits ) );
    table[0] = 0;
    table[1] = 2;
    for ( int i = 2; i < sizeOfTable; i++ ) {
        table[i] = 1;
    }

    std::ostringstream output;
    int x = 0;
    for ( ; sizeOfTable > 9; sizeOfTable-- ) {
        for ( int i = sizeOfTable - 1; i > 0; i-- ) {
            table[i] = x % i;
            x = 10 * table[i - 1] + x / i;
        }
        output << x;
    }

    for ( int i = 0; i < sizeOfTable; i++ ) {
        //std::cout << table[i] << std::endl;
    }

    return output.str();
}

void display( std::future<std::string> &aFutureValue, int theDecimals ) {
    aFutureValue.wait();
    std::cout << "e with " << theDecimals << " decimals\n"
              << aFutureValue.get() << std::endl;
}

int main() {
    std::future<std::string> eWidth1 = std::async( std::launch::async, &computeE, 20 );
    std::future<std::string> eWidth2 = std::async( std::launch::async, &computeE, 1000 );
    display( eWidth1, 20 );
    display( eWidth2, 1000 );
    return ( 0 );
}