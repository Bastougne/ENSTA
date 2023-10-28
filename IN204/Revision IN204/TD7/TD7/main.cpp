//
//  main.cpp
//  TD7
//
//  Created by Kazem Ammar on 13/11/2021.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Counter.hpp"
#include "GraphicalObject.hpp"


int main() {
    
//    ForwardCounter Objet1 (3,7);
//    BackwardCounter Objet2(2,7);
//
//    testNext(Objet1);
//    std::cout << "Hello, World!\n";
//    testNext(Objet2);
//
//    VerboseForwardCounter Objet3(1,10);
//    std::cout<<Objet3<<std::endl;
//    testForwardCounter(Objet3);

std::vector<GraphicalObject*> Object = createGraphicalObjects(10);
drawGraphicalObjects(Object);
deleteGraphicalObjects(Object);
    
    return 0;
}
