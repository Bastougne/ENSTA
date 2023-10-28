#include "counter.hpp"
#include <iostream>

void useObjectA() {
    ForwardCounter Counter1;
    Counter1.setMax( 3 );
    Counter1.reset();
    ForwardCounter Counter2( Counter1 );
    for ( unsigned i = 0; i <= 5; i++ ) {
        std::cout << "Valeur des compteurs (" << Counter1.counter << ", " << Counter2.counter << ")" << std::endl;
        Counter1.increment();
        Counter2.increment();
    }
}

void myfunctionA() {
    BaseCounter counter;
    std::cout << counter.getCounter() << std::endl;
    std::cout << counter.getMax() << std::endl;
}

void myfunctionB() {
    BaseCounter *counter = new BaseCounter();
    std::cout << counter->getCounter() << std::endl;
    std::cout << counter->getMax() << std::endl;
    delete counter;
}

int main() {
    useObjectA();
    return ( 0 );
    BiDiCounter MyBiDiCounter( 0, 5 );
    MyBiDiCounter.print();
    for ( unsigned i = 0; i <= 8; i++ ) {
        MyBiDiCounter.decrement();
        MyBiDiCounter.print();
    }
    return ( 0 );
}
