#ifndef sort_hpp
#define sort_hpp

#include <iostream>
#include <vector>

class Base {
  public:
    virtual bool isGreater( const Base & ) const = 0;
    virtual void print() const = 0;
};

void insertion_sort( std::vector<int> &anArray );

void print( std::vector<Base *> anArray );

#endif