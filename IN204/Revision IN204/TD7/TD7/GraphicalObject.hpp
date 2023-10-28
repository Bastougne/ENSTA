//
//  GraphicalObject.hpp
//  TD7
//
//  Created by Kazem Ammar on 13/11/2021.
//

#ifndef GraphicalObject_hpp
#define GraphicalObject_hpp

#include <iostream>
#include <stdio.h>

class GraphicalObject
{
public:
    virtual void draw () const = 0 ;
    virtual ~GraphicalObject() { std::cout << "& Delete GraphicalObject \n"; }
 
};
 
class Line: public virtual GraphicalObject
{
public:
    virtual void draw () const
    {
        std::cout << "Line";
    }
    ~Line()
    {
        std::cout << "Delete Line\n";
    }

};
 
class Circle: public virtual GraphicalObject
{
public:
    virtual void draw() const
    {
        std::cout << " Circle";
    }
    ~Circle  ()
    {
        std::cout << "Delete Circle  \n";
    }
};

std::vector<GraphicalObject*> createGraphicalObjects(int theSize);
void drawGraphicalObjects(std::vector<GraphicalObject*>& theGraphicalObjects);
void deleteGraphicalObjects(std::vector<GraphicalObject*>& theGraphicalObjects);


#endif /* GraphicalObject_hpp */
