//
//  main.cpp
//  TD2
//
//  Created by Kazem Ammar on 11/11/2021.
//

#include <iostream>
#include "Counter.hpp"

void testMyBiDiCounter()
{
    MyBiDiCounter counterA;
    counterA.setMax(4);
    counterA.reset();
    counterA.print();
    for(int i=0; i < 6; i++)
    {
        counterA.increment();
        counterA.print();
    }
    for(int i=0; i < 6; i++)
    {
        counterA.decrement();
        counterA.print();
    }
}

int main(int argc, const char * argv[]) {
    
    //testMyBiDiCounter();
    
    MyBiDiCounter CounterA(3,6);
    MyBiDiCounter CounterB(CounterA);
    CounterB.print();
    
    return 0;
}
