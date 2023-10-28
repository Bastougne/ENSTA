//
//  generic_sort.hpp
//  TD3
//
//  Created by Kazem Ammar on 12/11/2021.
//

#ifndef generic_sort_hpp
#define generic_sort_hpp

#include<iostream>
#include<stdlib.h>
#include<random>
#include<vector>


std::random_device rd;
std::minstd_rand gen(rd());

namespace generic
{
    template<typename T>
    struct greater_traits
    {
    public:
        static bool is_greater(T aValue, T anotherValue)
        {
            return (aValue>anotherValue);
        }
    };

    template<typename T>
    struct lower_traits
    {
    public:
        static bool is_greater(T aValue, T anotherValue)
        {
            return (aValue<anotherValue);
        }
    };
    

    template<typename T, typename genType>
    void populate_with_randoms(std::vector<T>& theVector, int theNumberOfValues, genType theMinValue, genType theMaxValue)
    {
        std::uniform_int_distribution<> distribution(theMinValue, theMaxValue);
        theVector.clear();
        
        for(int i=0; i<theNumberOfValues; ++i)
        {
            int randomValue = distribution(gen);
            theVector.push_back(randomValue);
        }
    }

    template<typename T>
    void print_vector(const std::vector<T>& anArray)
    {
        size_t length = anArray.size();
        std::cout<<"[";
        for (int i=0; i< length-1; ++i) {
            std::cout<<anArray[i]<<",";
        }
        std::cout<< anArray[length-1] << "]" << std::endl;
    }

    template<typename T, typename sortTraits = greater_traits<T>>
    void simple_sort(std::vector<T>& theValues, sortTraits* = NULL)
    {
        for (int i = 0; i<theValues.size(); i++)
            {
                for (int j = i + 1; j< theValues.size(); j++)
                {
                    if (sortTraits::is_greater(theValues[i], theValues[j]))
                    {
                        int Temp = theValues[i];
                        theValues[i] = theValues[j];
                        theValues[j] = Temp;
                    }
                }
            }
    }
}

#endif /* generic_sort_hpp */
