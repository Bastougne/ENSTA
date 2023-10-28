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
    
    void print() const
    {
        std::cout << "Compteur: " << counter << "/" << max << std::endl;
    }
};


class MyBiDiCounter: public MyCounter
{
public:
    MyBiDiCounter() : MyCounter() {}
    explicit MyBiDiCounter(unsigned theMax) : MyCounter(theMax) {}
    MyBiDiCounter(unsigned theCounter,unsigned theMax) : MyCounter(theCounter, theMax) {}
    MyBiDiCounter(const MyBiDiCounter& anotherCounter) : MyCounter(anotherCounter.counter){}
 
    void decrement()
    {
        if(counter == 0)
            counter = max;
        else
            counter --;
    }
    using MyCounter::increment;
    
    void increment(unsigned value)
    {
        if(counter + value < max)
            counter += value;
        else
            counter = (counter + value) % max;
    }
};

class MyAdvCounter : public MyCounter
{
public:
    MyAdvCounter() : MyCounter() {}
    explicit MyAdvCounter(unsigned theMax) : MyCounter(theMax) {}
    MyAdvCounter(unsigned theCounter,unsigned theMax) : MyCounter(theCounter, theMax) {}
    MyAdvCounter(const MyAdvCounter& anotherCounter) : MyCounter(anotherCounter.counter){}
    
    void increment()
    {
        if (counter<max)
        {
            counter = counter + 1;
        }
        else
        {
            counter = max;
        }
    }
};

#endif /* Counter_hpp */
