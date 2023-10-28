//
//  main.cpp
//  TD3
//
//  Created by Kazem Ammar on 12/11/2021.
//

#include <stdio.h>
#include <iostream>
#include<vector>
#include "simple_sort.hpp"
#include "generic_sort.hpp"

int main(int argc, const char * argv[]) {
    
//    std::vector<int> aVector;
//    
//    monomorphic::populate_with_randoms(aVector, 10, 1, 10);
//    monomorphic::print_vector(aVector);
//
//    monomorphic::simple_sort(aVector);
//    monomorphic::print_vector(aVector);
    
    
    std::vector<int> values;
    generic::populate_with_randoms(values, 10, 20, 40);
    generic::print_vector(values);
    generic::simple_sort(values);
    generic::print_vector(values);

    std::vector<float> floatValues;
    generic::populate_with_randoms(floatValues, 10, 20.0, 40.0);
    generic::print_vector(floatValues);
    generic::simple_sort(floatValues);
    generic::print_vector(floatValues);

    std::vector<char> charValues;
    generic::populate_with_randoms(charValues, 10, 'A', 'Z');
    generic::print_vector(charValues);
    generic::simple_sort(charValues);
    generic::print_vector(charValues);

    std::cout<<generic::greater_traits<int>::is_greater(3, 2)<<std::endl;
    
    std::vector<int> array;
    generic::populate_with_randoms(array, 10, 1, 10);
    generic::print_vector(array);
    std::cout << "\n";
    generic::simple_sort(array);
    generic::print_vector(array);
    std::cout << "\n";
    generic::simple_sort<int, generic::lower_traits<int>>(array);
    generic::print_vector(array);
    return 0;
}
