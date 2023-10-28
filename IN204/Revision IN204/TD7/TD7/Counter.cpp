//
//  Counter.cpp
//  TD7
//
//  Created by Kazem Ammar on 13/11/2021.
//

#include "Counter.hpp"

void testNext(BaseCounter& aCounter)
{
    for(int i=0; i<10;++i)
    {
        aCounter.next();
        std::cout<<aCounter;
    }
}

void testForwardCounter(ForwardCounter& aCounter)
{
    for(int i = 0 ; i < 10 ; i++)
    {
        aCounter.increment();
        std::cout<<aCounter;
        
    }
}
