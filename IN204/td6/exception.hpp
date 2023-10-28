#ifndef exception_hpp
#define exception_hpp

#include <exception>

class extended_exception : public std::runtime_error {
  private:
    int catchNumber = 0;

  public:
    explicit extended_exception( const std::string &aMessage ) : runtime_error( aMessage ) {}

    explicit extended_exception( const char *aMessage ) : runtime_error( aMessage ) {}

    void catched() {
        catchNumber++;
    }

    int getCatchNumber() const {
        return ( catchNumber );
    }
};

#endif
