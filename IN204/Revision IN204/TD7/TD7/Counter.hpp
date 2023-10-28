//
//  Counter.hpp
//  TD7
//
//  Created by Kazem Ammar on 13/11/2021.
//

#ifndef Counter_hpp
#define Counter_hpp

#include <iostream>
#include <stdio.h>

class BaseCounter
{
protected:
    unsigned counter;
    unsigned max;
 
public:
    unsigned getCounter() const
    {
        return counter;
    }
    unsigned getMax() const
    {
        return max;
    }
    void reset()
    {
        counter = 0;
    }
    void set(unsigned value)
    {
        counter = value;
    }
    void setMax(unsigned value)
    {
        max = value;
        if(value > counter)
            counter = counter % max;
    }
    
    virtual void next() = 0;
    virtual void next(unsigned) = 0;
    
    BaseCounter(): counter(0), max(0) {}
    BaseCounter(unsigned theCounter, unsigned theMax) : counter(theCounter), max(theMax) {}
    explicit BaseCounter(unsigned theMax): max(theMax), counter(0) {}
    BaseCounter(const BaseCounter& anotherCounter): counter(anotherCounter.counter), max(anotherCounter.max) {}
    ~BaseCounter() {}
    
    friend std::ostream& operator<<(std::ostream& os, const BaseCounter& Counter);
    
    virtual const char* getClassName() const=0;
    
//    virtual void reachMaximum() = 0;
};
 
inline std::ostream& operator<< (std::ostream& os, const BaseCounter& Counter)
{
    os << Counter.getClassName()<<"(" << Counter.counter << "," << Counter.max << ")" << std::endl;
    return os;
}

class ForwardCounter: public virtual BaseCounter
{
public:
    virtual void increment()
    {
        if(counter < max)
        {
            counter = counter + 1;
        }
        else
        {
            counter=0;
        }
    }
    ForwardCounter() : BaseCounter() {}
    ForwardCounter(const ForwardCounter& aCounter) : BaseCounter(aCounter) {}
    explicit ForwardCounter(unsigned theMaxValue) : BaseCounter(0, theMaxValue) {}
    ForwardCounter(unsigned theCounter, unsigned theMaxValue) : BaseCounter(theCounter, theMaxValue) {}
    
    virtual void next()
    {
        increment();
    }
    virtual void next(unsigned aNumberOfSteps)
    {
        while (aNumberOfSteps>0) {
            increment();
            --aNumberOfSteps;
        }
    }
    virtual const char* getClassName() const
    {
        return ("ForwardCounter: ");
    }
};
 
class BackwardCounter: public virtual BaseCounter
{
public:
    void decrement()
    {
        if(counter > 0)
        counter = counter - 1;
        else
        counter=max;
    }
    BackwardCounter() : BaseCounter() {}
    BackwardCounter(const ForwardCounter& aCounter) : BaseCounter(aCounter) {}
    explicit BackwardCounter(unsigned theMaxValue) : BaseCounter(0, theMaxValue) {}
    BackwardCounter(unsigned theCounter, unsigned theMaxValue) : BaseCounter(theCounter, theMaxValue) {}
    
    virtual void next()
    {
        decrement();
    }
    
    virtual void next(unsigned aNumberOfSteps)
    {
        while (aNumberOfSteps>0) {
            decrement();
            --aNumberOfSteps;
        }
    }
    
    virtual const char* getClassName() const
    {
        return ("BackwardCounter: ");
    }
};

class BiDiCounter: public ForwardCounter, public BackwardCounter
{
public:
    
    BiDiCounter(): ForwardCounter(), BackwardCounter() {}
    
    BiDiCounter(const BiDiCounter& aCounter): ForwardCounter((const ForwardCounter&) aCounter), BackwardCounter((const BackwardCounter&)aCounter), BaseCounter((const BaseCounter&) aCounter)  {}
    
    BiDiCounter(unsigned theMaxValue): BiDiCounter(0, theMaxValue) {}
    BiDiCounter(unsigned theCounter, unsigned theMaxValue): ForwardCounter(theCounter, theMaxValue), BackwardCounter(theCounter, theMaxValue),
        BaseCounter(theCounter, theMaxValue) {}
    
    void next()
    {
        ForwardCounter::next();
    }
    void next(unsigned aNumberOfSteps)
    {
        ForwardCounter::next(aNumberOfSteps);
    }
    
    void getClassName()
    {
        std::cout<<"BiDiCounter: ";
    }
    
    virtual const char* getClassName() const
    {
        return ("BiDiCounter: ");
    }
};


void testNext(BaseCounter& aCounter);
void testForwardCounter(ForwardCounter& aCounter);


class VerboseForwardCounter : public virtual ForwardCounter
{
public:
    void virtual increment()
    {
        if (counter < max)
            counter = counter + 1;
        else
        {
            std::cout << "Maximal value: " << max << " has been reached." << std::endl;
            counter = 0;
        }
    }
 
    VerboseForwardCounter() : BaseCounter() {}
    VerboseForwardCounter(const VerboseForwardCounter& aCounter) : BaseCounter(aCounter) {}
    explicit VerboseForwardCounter(unsigned theMaxValue) : BaseCounter(0, theMaxValue) {}
    VerboseForwardCounter(unsigned int theCounter, unsigned int theMaxValue) : BaseCounter(theCounter, theMaxValue) {}
 
};

#endif /* Counter_hpp */
