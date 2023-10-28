#include "graphical.hpp"

int main() {
    auto graphicalObjects = createGraphicalObjects( 10 );
    drawGraphicalObjects( graphicalObjects );
    deleteGraphicalObjects( graphicalObjects );
    return ( 0 );
}