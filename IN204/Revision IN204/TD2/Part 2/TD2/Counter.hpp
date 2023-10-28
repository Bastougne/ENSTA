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

class BaseCounter
{
protected:
    unsigned counter;
    unsigned max;
 
public:
    
    BaseCounter(): counter(0), max(0) {}
    BaseCounter(unsigned theCounter, unsigned theMax): counter(theCounter), max(theMax){}
    explicit BaseCounter(unsigned theMax): max(theMax), counter(0){}
    BaseCounter(const BaseCounter& anotherCounter): counter(anotherCounter.counter), max(anotherCounter.max){}
    ~BaseCounter()
    {
        std::cout << "Destruction: BaseCounter" << std::endl;
    }
    
    unsigned getCounter() const { return counter; }
    unsigned getMax() const { return max; }

    void reset() { counter = 0; }
    void set(unsigned value) { counter = value; }
    void setMax(unsigned value)
    {
        max = value;
        if(value > counter)
            counter = counter % max;
    }
    
    void print() const
    {
        std::cout << "Compteur : " << counter << "/" << max << std::endl;
    }
};

class ForwardCounter : public virtual BaseCounter
{
public:
    ForwardCounter():BaseCounter(){}
    ForwardCounter(const ForwardCounter& Objet):BaseCounter(Objet){}
    ForwardCounter(unsigned ValeurMax):BaseCounter(ValeurMax){}
    ForwardCounter(unsigned theCounter, unsigned theMax):BaseCounter(theCounter,theMax){}
    
    void increment()
    {
        if(counter == max)
            counter = 0;
         else
            counter ++;
    }
    
    ~ForwardCounter()
    {
        std::cout << "Destruction: ForwardCounter" << std::endl;
    }
};

class BackwardCounter : public virtual BaseCounter
{
public:
    BackwardCounter():BaseCounter(){}
    BackwardCounter(const BackwardCounter& Objet):BaseCounter(Objet){}
    BackwardCounter(unsigned ValeurMax):BaseCounter(ValeurMax){}
    BackwardCounter(unsigned theCounter, unsigned theMax):BaseCounter(theCounter,theMax){}
    
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
    
    ~BackwardCounter()
    {
        std::cout << "Destruction: BackwardCounter" << std::endl;
    }
};

class BiDiCounter: public ForwardCounter, public BackwardCounter
{
    public:
        BiDiCounter() : BaseCounter() {}
        BiDiCounter(const BiDiCounter& aCounter) : BaseCounter(aCounter) {}
        BiDiCounter(unsigned theMaxValue) : BiDiCounter(0, theMaxValue) {}
        BiDiCounter(unsigned theCounter, unsigned theMaxValue) : BaseCounter(theCounter, theMaxValue) {}
    
    ~BiDiCounter()
    {
        std::cout << "Destruction: BiDiCounter" << std::endl;
    }
};
#endif /* Counter_hpp */
