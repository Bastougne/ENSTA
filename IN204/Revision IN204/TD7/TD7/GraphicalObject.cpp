//
//  GraphicalObject.cpp
//  TD7
//
//  Created by Kazem Ammar on 13/11/2021.
//

#include "GraphicalObject.hpp"
#include <vector>

std::vector<GraphicalObject*> createGraphicalObjects(
    int theSize)
{
    std::vector<GraphicalObject*> graphicalObjects(theSize);
    for(int i=0; i < theSize; i++)
    {
       graphicalObjects[i] = new Line();
       graphicalObjects[++i] = new Circle();
    }
    return graphicalObjects;
}

void drawGraphicalObjects(std::vector<GraphicalObject*>& theGraphicalObjects)
{
    for(auto it = theGraphicalObjects.begin();
        it < theGraphicalObjects.end(); it++)
    {
       (*it)->draw();
    }
}

void deleteGraphicalObjects(std::vector<GraphicalObject*>& theGraphicalObjects)
{
    for(auto it = theGraphicalObjects.begin();
        it < theGraphicalObjects.end(); it++)
    {
       delete *it;
    }
}
