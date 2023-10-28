//
//  main.cpp
//  TD4
//
//  Created by Kazem Ammar on 12/11/2021.
//

#include <iostream>
#include <vector>       // std::vector
#include <algorithm>

template <class inputIterator, class T>
inputIterator upper(inputIterator first, inputIterator end, const T& theValue)
{
    for (; first != end; first++)
    {
        if (*first > theValue)
            return first;
    }
    return end;
}

template <class inputIterator>
void print(inputIterator first, inputIterator end)
{
    std::cout<<"[";
    for (; first!=end-1; ++first) {
        std::cout<<*first<<", ";
    }
    
    std::cout<<*first<<"]"<<std::endl;
}

int testUpper()
{
    int myints[] = { 10,20,30,30,20,10,10,20 };
    std::vector<int> v(myints, myints + 8);
    std::vector<int>::iterator up = upper(v.begin(), v.end(), 20);
    print(v.begin(), v.end());
    std::cout << "Before sort: first value greater than 20  at position " << (up - v.begin()) << '\n';
    
    sort(v.begin(),v.end());
    up = upper(v.begin(), v.end(), 20);
    print(v.begin(), v.end());
    std::cout << "After sort: first value greater than 20  at position " << (up - v.begin()) << '\n';
    return 0;
}

int main(int argc, const char * argv[]) {
    testUpper();
    std::cout << "Hello, World!\n";
    return 0;
}
