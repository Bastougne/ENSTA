#include <iostream>
#include <vector>

class GraphicalObject {
  public:
    virtual void draw() const = 0;

    virtual ~GraphicalObject() {
        std::cout << "Delete GraphicalObject\n";
    }
};

class Line : public GraphicalObject {
  public:
    virtual void draw() const {
        std::cout << "Draw Line\n";
    }

    ~Line() {
        std::cout << "Delete Line\n";
    }
};

class Circle : public GraphicalObject {
  public:
    virtual void draw() const {
        std::cout << "Draw Circle\n";
    };

    ~Circle() {
        std::cout << "Delete Circle\n";
    }
};

std::vector<GraphicalObject *> createGraphicalObjects( int size ) {
    std::vector<GraphicalObject *> graphicalObjects( size );
    for ( int i = 0; i < size; i++ ) {
        graphicalObjects[i] = new Line();
        graphicalObjects[++i] = new Circle();
    }
    return ( graphicalObjects );
}

void drawGraphicalObjects( std::vector<GraphicalObject *> &theGraphicalObjects ) {
    for ( auto it = theGraphicalObjects.begin(); it < theGraphicalObjects.end(); it++ ) {
        ( *it )->draw();
    }
}

void deleteGraphicalObjects( std::vector<GraphicalObject *> &theGraphicalObjects ) {
    for ( auto it = theGraphicalObjects.begin(); it < theGraphicalObjects.end(); it++ ) {
        delete *it;
    }
}
