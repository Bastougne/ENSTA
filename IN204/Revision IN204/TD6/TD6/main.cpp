//
//  main.cpp
//  TD6
//
//  Created by Kazem Ammar on 13/11/2021.
//

#include <iostream>
#include "math.hpp"

void test_divide() noexcept;

void test_divide() noexcept
{
  double i, j;
  for(;;)
  {
    std::cout << "Le numerateur (0 pour arreter): ";
    std::cin >> i;
    if(i == 0)
    {
        break;
        
    }
    std::cout << " Le denominateur : ";
    std::cin >> j;
    try
    {
        std::cout << "Resultat: " << divide(i,j) << std::endl;
    }
    catch(division_by_zero anException)
    {
        std::cout << "Erreur: " << anException.what() << std::endl;
    }
  }
}

double successive_division(double i) noexcept(false);
 
void test_succesive_division() noexcept
{
    double i;
    std::cout << "The numerator: ";
    std::cin >> i;
    try {
        successive_division(i);
    }
    catch (extended_divide_by_zero e) {
        e.catched();
        std::cout << "Division by zero occurred after " << e.getCatchNumber() << " divisions" << std::endl;
    }
}
 
double successive_division(double i) noexcept(false)
{
  double j;
  std::cout << "Next divisor (-1 to stop sequence): ";
  std::cin >> j;
  if (j == -1)
    return i;
  try {
    successive_division(j);
    return divide(i,j);
  }
  catch (extended_divide_by_zero e)
  {
    e.catched();
      throw e;
  }
}

int main() {
    test_succesive_division();
    std::cout << "Hello, World!\n";
    return 0;
}
