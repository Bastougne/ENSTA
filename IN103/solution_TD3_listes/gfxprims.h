/**
   Very minimal graphics primitives using SDL.
   François Pessaux 2012 - ...
   Can be freely reused, modified, distributed, trashed...
*/

#ifndef __GFXPRIMS_H__
#define __GFXPRIMS_H__
#include <SDL.h>

/** \brief Get the RGB color components of a point at (x, y) coordinates.
    Components are packed in a 32 bits int (T-R-G-B) with 8 bits for each
    component. */
Uint32 getPixel (SDL_Surface *surface, int x, int y) ;

/** \brief Draws a point at (x, y) coordinates with color given as RGB
    components. */
void renderPixel (int x, int y, Uint8 R, Uint8 G, Uint8 B) ;

/** \brief Draws a segment between 2 points (start and end points
    included).
    \param x1, y1 First point's coordinates.
    \param x2, y2 First point's coordinates. */
void line (int x1, int y1, int x2, int y2) ;

/** \brief Draws a circle between 2 points (start and end points
    included).
    \param x0, y0 Center.
    \param radius Radius of the circle
    \param R, G, B Color components for drawing. */
void renderCircle (int x0, int y0, int radius, Uint8 R, Uint8 G, Uint8 B) ;

extern SDL_Surface *g_screenSurface ;
#endif
