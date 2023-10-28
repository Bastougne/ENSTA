//
//  math.cpp
//  TD6
//
//  Created by Kazem Ammar on 13/11/2021.
//

#include <iostream>
#include "math.hpp"

double divide(double a, double b) noexcept(false)
{
    if(b==0)
    {
        throw extended_divide_by_zero();
        return b;
    }
    return a/b;
}
