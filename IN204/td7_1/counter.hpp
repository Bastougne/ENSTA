#ifndef COUNTER_HPP
#define COUNTER_HPP

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
        counter = value;
    }

    void setMax( unsigned value ) {
        max = value;
        if ( value > counter )
            counter = counter % max;
    }

    virtual void next() = 0;

    virtual void next( unsigned ) = 0;

  protected:
    BaseCounter() : counter( 0 ), max( 0 ) {}

    BaseCounter( unsigned theCounter, unsigned theMax ) : counter( theCounter ), max( theMax ) {}

    explicit BaseCounter( unsigned theMax ) : max( theMax ), counter( 0 ) {}

    BaseCounter( const BaseCounter &T ) : counter( T.counter ), max( T.max ) {}

    ~BaseCounter() {}
};

class ForwardCounter : public virtual BaseCounter {
  public:
    void increment() {
        if ( counter < max ) {
            counter++;
        } else {
            counter = 0;
        }
    }
    virtual void next() {
        increment();
    }
    virtual void next( unsigned steps ) {
        for ( unsigned i = 0; i < steps; i++ ) {
            increment();
        }
    }

    ForwardCounter() : BaseCounter() {}

    ForwardCounter( const ForwardCounter &T ) : BaseCounter( T ) {}

    explicit ForwardCounter( unsigned theMaxValue ) : ForwardCounter( 0, theMaxValue ) {}

    ForwardCounter( unsigned theCounter, unsigned theMaxValue ) : BaseCounter( theCounter, theMaxValue ) {}
};

class BackwardCounter : public virtual BaseCounter {
  public:
    void decrement() {
        if ( counter < 0 ) {
            counter--;
        } else {
            counter = max;
        }
    }
    virtual void next() {
        decrement();
    }
    virtual void next( unsigned steps ) {
        for ( unsigned i = 0; i < steps; i++ ) {
            decrement();
        }
    }

    BackwardCounter() : BaseCounter() {}

    BackwardCounter( const ForwardCounter &T ) : BaseCounter( T ) {}

    explicit BackwardCounter( unsigned theMaxValue ) : BackwardCounter( 0, theMaxValue ) {}

    BackwardCounter( unsigned theCounter, unsigned theMaxValue ) : BaseCounter( theCounter, theMaxValue ) {}
};

class BiDiCounter : public ForwardCounter, public BackwardCounter {
  public:
    virtual void next() {
        ForwardCounter::next();
    }

    virtual void next( unsigned steps ) {
        ForwardCounter::next( steps );
    }

    BiDiCounter() : ForwardCounter(), BackwardCounter() {}

    BiDiCounter( const BiDiCounter &T ) : ForwardCounter( T ), BackwardCounter( (const BackwardCounter &)T ), BaseCounter( T ) {}

    BiDiCounter( unsigned theMaxValue ) : BiDiCounter( 0, theMaxValue ) {}

    BiDiCounter( unsigned theCounter, unsigned theMax ) : ForwardCounter( theCounter, theMax ), BackwardCounter( theCounter, theMax ), BaseCounter( theCounter, theMax ) {}
};

template <class charT, class charTraits>
std::basic_ostream<charT, charTraits> &operator<<( std::basic_ostream<charT, charTraits> &aStream, const BaseCounter &T ) {
    aStream << T.counter << "/" << T.max;
    return ( aStream );
}

void testNext( BaseCounter & );

#endif // COUNTER_HPP