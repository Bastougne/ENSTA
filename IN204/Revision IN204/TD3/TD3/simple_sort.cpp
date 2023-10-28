//
//  simple_sort.cpp
//  TD3
//
//  Created by Kazem Ammar on 12/11/2021.
//

#include "simple_sort.hpp"
#include<iostream>
#include<stdlib.h>
#include <random>

//std::random_device rd;
//std::minstd_rand gen(rd());
//
//namespace monomorphic
//{
//
//    void populate_with_randoms(std::vector<int>& theVector, int theNumberOfValues, int theMinValue, int theMaxValue)
//    {
//        std::uniform_int_distribution<> distribution(theMinValue, theMaxValue);
//        theVector.clear();
//
//        for(int i=0; i<theNumberOfValues; ++i)
//        {
//            int randomValue = distribution(gen);
//            theVector.push_back(randomValue);
//        }
//    }
//
//    void print_vector(const std::vector<int>& anArray)
//    {
//        size_t length = anArray.size();
//        std::cout<<"[";
//        for (int i=0; i< length-1; ++i) {
//            std::cout<<anArray[i]<<",";
//        }
//        std::cout<< anArray[length-1] << "]" << std::endl;
//    }
//
//    void simple_sort(std::vector<int>& theValues)
//    {
//        for (int i = 0; i<theValues.size(); i++)
//            {
//                for (int j = i + 1; j< theValues.size(); j++)
//                {
//                    // Compare si les deux elements sont dans le bon ordre.
//                    if (theValues[i] > theValues[j])
//                    {
//                        // Procede a la permutation des deux elements
//                        int Temp = theValues[i];
//                        theValues[i] = theValues[j];
//                        theValues[j] = Temp;
//                    }
//                }
//            }
//    }
//
//}
