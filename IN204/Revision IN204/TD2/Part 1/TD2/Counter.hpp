//
//  Counter.hpp
//  TD2
//
//  Created by Kazem Ammar on 11/11/2021.
//

#ifndef Counter_hpp
#define Counter_hpp

#include <stdio.h>
#include <iostream>

class MyCounter
{
protected:
    unsigned counter;
    unsigned max;
 
public:
    unsigned getCounter() const { return counter; }
    unsigned getMax() const { return max; }
    void increment()
    {
       if(counter == max)
           counter = 0;
        else
           counter ++;
    }
    void reset() { counter = 0; }
    void set(unsigned value) { counter = value; }
    void setMax(unsigned value)
    {
        max = value;
        if(value > counter)
            counter = counter % max;
    }
 
    MyCounter(): counter(0), max(0) {}
    MyCounter(unsigned theCounter,
        unsigned theMax): counter(theCounter), max(theMax)
    {}
    explicit MyCounter(unsigned theMax):
        max(theMax), counter(0)
    {}
    MyCounter(const MyCounter& anotherCounter):
        counter(anotherCounter.counter),
        max(anotherCounter.max)
    {}
    ~MyCounter()
    {}
};


class MyBiDiCounter : public MyCounter
{
public:
    MyBiDiCounter():MyCounter(){}

    MyBiDiCounter(const MyBiDiCounter& Objet):MyCounter(Objet){}
    
    MyBiDiCounter(unsigned ValeurMax):MyCounter(ValeurMax){}
    
    MyBiDiCounter(unsigned theCounter, unsigned theMax):MyCounter(theCounter,theMax){}
    
    void decrement()
    {
        if (counter > 0)
        {
            counter--;
        }
        else
        {
            counter = max;
        }
    }
    void print() const
    {
        std::cout << "Compteur : " << counter << "/" << max << std::endl;
    }
};
#endif /* Counter_hpp */
