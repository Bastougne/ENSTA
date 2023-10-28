//
//  main.cpp
//  TD2
//
//  Created by Kazem Ammar on 11/11/2021.
//

#include <iostream>
#include "Counter.hpp"

//void testMyBiDiCounter()
//{
//    MyBiDiCounter counterA;
//    counterA.setMax(4);
//    counterA.reset();
//    counterA.print();
//    for(int i=0; i < 6; i++)
//    {
//        counterA.increment();
//        counterA.print();
//    }
//    for(int i=0; i < 6; i++)
//    {
//        counterA.decrement();
//        counterA.print();
//    }
//}

//void testFamilyOfCounters()
//{
//    ForwardCounter incCounter(0, 4);
//    BackwardCounter decCounter(0, 3);
//    BiDiCounter biDiCounter(0, 5);
//    for(int i=0; i < 6; i++)
//    {
//        incCounter.increment();
//        incCounter.print();
//    decCounter.decrement();
//        decCounter.print();
//        biDiCounter.increment();
//        biDiCounter.print();
//    }
//    for(int i=0; i < 6; i++)
//    {
//        biDiCounter.decrement();
//        biDiCounter.print();
//    }
//}

void testFamilyOfCounters()
{
    ForwardCounter incCounter(0, 4);
    BackwardCounter decCounter(0, 3);
    BiDiCounter biDiCounter(0, 5);
    for(int i=0; i < 6; i++)
    {
        incCounter.increment();
        incCounter.print();
    decCounter.decrement();
        decCounter.print();
        biDiCounter.increment();
        biDiCounter.print();
    }
    for(int i=0; i < 6; i++)
    {
        biDiCounter.decrement();
        biDiCounter.print();
    }
}

int main(int argc, const char * argv[]) {
    
    //testMyBiDiCounter();
    
    testFamilyOfCounters();
    
    return 0;
}
