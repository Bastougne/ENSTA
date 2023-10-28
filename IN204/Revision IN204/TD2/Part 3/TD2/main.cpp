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


void testNewIncMethod() {
    MyBiDiCounter bidiCounter1(0, 5);
    for(unsigned i = 0; i <= 5; i++)
    {
        bidiCounter1.increment(5);
        bidiCounter1.print();
    }
}

void testOldIncMethod() {
    MyBiDiCounter bidiCounter1(0, 5);
    for(unsigned i = 0; i <= 5; i++)
    {
        bidiCounter1.increment();
        bidiCounter1.print();
    }
}

void testMyAdvCounter()
{
    MyAdvCounter incCounter(0, 4);
    for(int i=0; i < 6; i++)
    {
        incCounter.increment();
        incCounter.print();
    }
}

void testCounter(MyCounter& unCompteur)
{
    for(int i=0; i < 6; i++)
    {
        unCompteur.increment();
        unCompteur.print();
    }
}
void testCounter(MyAdvCounter& unCompteur)
{
    for(int i=0; i < 6; i++)
    {
        unCompteur.increment();
        unCompteur.print();
    }
}
int main(int argc, const char * argv[]) {
    
    //testMyBiDiCounter();
    
    //testMyAdvCounter();
    
    MyAdvCounter Counter1(0,4);
    testCounter(Counter1);
    return 0;
}
