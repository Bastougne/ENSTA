//
//  main.cpp
//  TD5
//
//  Created by Kazem Ammar on 13/11/2021.
//

#include <iostream>
#include "complex.hpp"

extern Complex I;

int main(int argc, const char * argv[]) {
    Complex test1 = Complex::from_real_imaginary(2.0, 1.0);
    test1.print();
    
    Complex test2 = Complex::from_polar(10.0, 2.0);
    test2.print();
    std::cout << test1 << std::endl;
    
    
    Complex complexValue = 3.3 + 5 * I;
    
    complexValue.print();
    
    return 0;
}
