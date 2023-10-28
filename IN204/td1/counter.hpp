#ifndef BaseCounter_hpp
#define BaseCounter_hpp
#include <iostream>

class BaseCounter {

  public:
    unsigned counter;
    unsigned max;

    unsigned getCounter() const {
        return counter;
    }

    unsigned getMax() const {
        return max;
    }

    void reset() {
        counter = 0;
    }

    void set( unsigned value ) {
        counter = ( value <= max ) ? value : counter; // if value <= max, counter = value, else counter = counter
    }

    void setMax( unsigned value ) {
        if ( counter >= value ) {
            counter = 0;
        }
        max = value;
    }

    void print() {
        std::cout << "Compteur : " << counter << "/" << max << std::endl;
    }

    BaseCounter() {
        counter = 0;
        max = 0;
    }

    BaseCounter( int value, unsigned maximum ) {
        counter = value;
        max = maximum;
    }

    explicit BaseCounter( unsigned maximum ) : BaseCounter( 0, maximum ) {}

    BaseCounter( const BaseCounter &T ) {
        counter = T.counter;
        max = T.max;
    }

    ~BaseCounter() {
        std::cout << "Mort du compteur à la valeur " << counter << std::endl;
    }
};

class ForwardCounter : virtual public BaseCounter {

  public:
    void increment() {
        if ( counter < max ) {
            counter++;
        } else {
            counter = 0;
        }
    }

    ForwardCounter() : BaseCounter() {}

    explicit ForwardCounter( unsigned maximum ) : BaseCounter( maximum ) {}

    ForwardCounter( int value, unsigned maximum ) : BaseCounter( value, maximum ) {}

    ForwardCounter( const ForwardCounter &T ) : BaseCounter( T ) {}
};

class BackwardCounter : virtual public BaseCounter {

  public:
    void decrement() {
        if ( counter > 0 ) {
            counter--;
        } else {
            counter = max;
        }
    }

    BackwardCounter() : BaseCounter() {}

    explicit BackwardCounter( unsigned maximum ) : BaseCounter( maximum ) {}

    BackwardCounter( int value, unsigned maximum ) : BaseCounter( value, maximum ) {}

    BackwardCounter( const BackwardCounter &T ) : BaseCounter( T ) {}
};

class BiDiCounter : public ForwardCounter, public BackwardCounter {

  public:
    void increment( unsigned value ) {
        if ( counter + value < max ) {
            counter = counter + value;
        } else {
            counter = ( counter + value ) % max;
        }
    }

    using ForwardCounter::increment;

    BiDiCounter() : ForwardCounter(), BackwardCounter() {}

    BiDiCounter( const BiDiCounter &T ) : ForwardCounter( T ), BackwardCounter( T ), BaseCounter( T ) {}

    BiDiCounter( unsigned maximum ) : BiDiCounter( 0, maximum ) {}

    BiDiCounter( unsigned theCounter, unsigned theMaxValue ) : ForwardCounter(), BackwardCounter(), BaseCounter( theCounter, theMaxValue ) {}
};

#endif
