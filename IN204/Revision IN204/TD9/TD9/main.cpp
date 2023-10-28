//
//  main.cpp
//  TD9
//
//  Created by Kazem Ammar on 14/11/2021.
//

#include <iostream>
#include <vector>


void print(std::initializer_list<int> arguments)
{
    auto it = arguments.begin(), end_it = arguments.end();
    if (it != end_it)
    {
        std::cout << *it;
        while (++it != end_it)
        {std::cout << ", " << *it;}
    }
}

int main(int argc, const char * argv[]) {
    std::initializer_list<int> list_of_values = {1, 3, 4, 2 };
    print(list_of_values);
    std::cout << "Hello, World!\n";
    return 0;
}
