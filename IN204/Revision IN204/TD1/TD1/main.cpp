//
//  main.cpp
//  TD1
//
//  Created by Kazem Ammar on 11/11/2021.
//

#include <iostream>
#include <stdio.h>
#include "counter.hpp"

void useObjectA()
{
    MyCounter Counter1(2);
    MyCounter Counter2(4);
    for(unsigned i = 0; i <= 5; i++)
    {
        std::cout<< "Valeur des compteurs (" << Counter1.counter << ", " << Counter2.counter << ")" << std::endl;
        Counter1.increment();
        Counter2.increment();
    }
}

void myfunctionA()
{
  MyCounter counter;
  std::cout << counter.getCounter() << std::endl;
  std::cout << counter.getMax() << std::endl;
}
 
void myfunctionB()
{
  MyCounter* counter = new MyCounter();
  std::cout << counter->getCounter() << std::endl;
  std::cout << counter->getMax() << std::endl;
  delete counter;
}

void myfunctionC()
{
    MyCounter Counter1(2);
    MyCounter Counter2(Counter1);
    std::cout << Counter2.getCounter() << std::endl;
    std::cout << Counter2.getMax() << std::endl;
}

int main(int argc, const char * argv[]) {
    useObjectA();
    //myfunctionA();
    //myfunctionB();
    //myfunctionC();
    std::cout << "Hello, World!\n";
    return 0;
}
