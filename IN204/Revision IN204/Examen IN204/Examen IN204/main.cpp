//
//  main.cpp
//  Examen IN204
//
//  Created by Kazem Ammar on 13/11/2021.
//

#include <iostream>
#include <stdio.h>
#include "key_value_pair.hpp"
#include <complex>
#include <vector>

template<class keyT , class valueT>
void simple_sort(std::vector<key_value_pair<keyT, valueT>>& Tableau)
{
    for (int i = 0; i<Tableau.size(); i++)
        {
            for (int j = i + 1; j< Tableau.size(); j++)
            {
                if (Tableau[i]>=Tableau[j])
                {
                    key_value_pair<keyT, valueT> Temp = Tableau[i];
                    Tableau[i] = Tableau[j];
                    Tableau[j] = Temp;
                }
            }
        }
}
void print(const std::vector<key_value_pair<std::string, float>>& Tableau)
{
    std::cout<<"[";
    for (int i=0; i<Tableau.size()-1; ++i) {
        std::cout<<Tableau[i].getKey()<<",";
    }
    std::cout<<Tableau[Tableau.size()-1].getKey();
    std::cout<<"]"<<std::endl;
}

int main(int argc, const char * argv[]) {
//    key_value_pair Objet1(1,"kazem");
//    key_value_pair Objet2(2,"kazem");
//    bool reponse = Objet1<=Objet2;
//    std::cout << reponse << std::endl;
//    key_value_pair<std::complex<int>, std::string> test1;
//    key_value_pair<std::complex<double>, std::string> test2(1.0,"kazem");
//
//    bool reponse = test1<=test2;
//    std::cout << reponse << std::endl;
    
    
    std::vector<key_value_pair<std::string, float>> listOfIdentifiers;
    listOfIdentifiers.push_back(key_value_pair<std::string, float>("mot", 10));
    listOfIdentifiers.push_back(key_value_pair<std::string, float>("le", 100));
    listOfIdentifiers.push_back(key_value_pair<std::string, float>("la", 80));
    listOfIdentifiers.push_back(key_value_pair<std::string, float>("du", 40));
    
    
//    key_value_pair<std::string, float> Objet1("kazez", 10);
//    key_value_pair<std::string, float> Objet2("kaze", 100);
//
//
//    bool reponse = Objet1<=Objet2;
//
//    std::cout << reponse << std::endl;
    
    simple_sort(listOfIdentifiers);
    print(listOfIdentifiers);
    
    key_value_pair<std::string, float> Objet("du", 40);
    
    std::cout<<Objet;
    return 0;
}
