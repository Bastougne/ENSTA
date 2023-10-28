//
//  math.hpp
//  TD6
//
//  Created by Kazem Ammar on 13/11/2021.
//

#ifndef math_hpp
#define math_hpp

#include <stdio.h>
#include <iostream>
#include <exception>


class division_by_zero : public std::runtime_error
{
public:
    division_by_zero(): std::runtime_error("Division by zero") {}
};

double divide(double a, double b) noexcept(false);


class extended_exception : public std::runtime_error
{
private:
    unsigned int nombre = 0;
public:
    extended_exception() : std::runtime_error("Error Captured"){}
    extended_exception(const std::string& aMessage): std::runtime_error(aMessage) {}
    extended_exception(const char* aMessage): runtime_error(aMessage) {}
    
    void catched()
    {
        nombre++;
    }
        
    int getCatchNumber() const
    {
        return nombre;
    }
};
class extended_divide_by_zero : public extended_exception
{
public:
    extended_divide_by_zero() : extended_exception("Division by zero") {}
};

#endif /* math_hpp */
