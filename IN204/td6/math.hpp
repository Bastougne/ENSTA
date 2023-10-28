#ifndef math_hpp
#define math_hpp

#include "exception.hpp"
#include <exception>
#include <stdexcept>

class division_by_zero : public std::runtime_error {
  public:
    division_by_zero() : std::runtime_error( "Dénominateur nul\n" ) {}
};

class extended_division_by_zero : public extended_exception {
  public:
    extended_division_by_zero() : extended_exception( "Division by zero" ) {}
};

double divide( double a, double b );
/* avant : double divide( double a, double b ) throw( division_by_zero ) et idem dans cpp; */

#endif
