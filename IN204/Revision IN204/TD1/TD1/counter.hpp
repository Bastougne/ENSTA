//
//  counter.hpp
//  TD1
//
//  Created by Kazem Ammar on 11/11/2021.
//

#ifndef counter_hpp
#define counter_hpp

#include <iostream>
#include <stdio.h>

struct MyCounter
{
    unsigned counter;
    unsigned max;
 
    MyCounter() // constructeur par default
    {
        counter = 0;
        max = 0;
    }
    explicit MyCounter(unsigned ValeurMax)
    {
        counter = 0;
        max = ValeurMax;
    }
    explicit MyCounter(unsigned ValeurMax, unsigned ValeurCompteur)
    {
        counter = ValeurCompteur;
        max = ValeurMax;
    }
    
    explicit MyCounter(const MyCounter& Objet)
    {
        counter = Objet.counter;
        max = Objet.max;
    }
    unsigned getCounter() const;
    unsigned getMax() const;
    void increment();
 
    void reset();
 
    void set(unsigned value);
 
    void setMax(unsigned value);
    
    ~MyCounter()
    {
        std::cout << "Delete counter: " << this
        << " (" << counter << "," << max << ")" << std::endl;
    }
};

#endif /* counter_hpp */
