/**
   Very minimal graphics primitives using SDL.
   François Pessaux 2012 - ...
   Can be freely reused, modified, distributed, trashed...
*/

#include <SDL.h>
#include "gfxprims.h"


SDL_Surface *g_screenSurface = NULL ;


/** \brief Get the RGB color components of a point at (x, y) coordinates.
    Components are packed in a 32 bits int (T-R-G-B) with 8 bits for each
    component. */
Uint32 getPixel (SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel ;
  Uint8 *p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp ;
  switch (bpp) {
  case 1: return (*p) ;
  case 2: return (*(Uint16*) p) ;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return (p[0] << 16 | p[1] << 8 | p[2]) ;
    else return (p[0] | p[1] << 8 | p[2] << 16) ;
  case 4: return (*(Uint32 *)p) ;
  default: return (0) ;
  }
}



void renderPixel (int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  Uint32 color = SDL_MapRGB (g_screenSurface->format, R, G, B) ;

  switch (g_screenSurface->format->BytesPerPixel) {
  case 1: { // Assuming 8-bpp
    Uint8 *bufp;
    bufp = (Uint8*) g_screenSurface->pixels + y*g_screenSurface->pitch + x ;
    *bufp = color;
    }
    break ;

  case 2: { // Probably 15-bpp or 16-bpp
    Uint16 *bufp;
    bufp = (Uint16*) g_screenSurface->pixels + y*g_screenSurface->pitch/2 + x ;
    *bufp = color;
    }
    break ;

  case 3: { // Slow 24-bpp mode, usually not used
    Uint8 *bufp;
    bufp = (Uint8*) g_screenSurface->pixels + y*g_screenSurface->pitch + x * 3;
    if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
      bufp[0] = color;
      bufp[1] = color >> 8;
      bufp[2] = color >> 16;
    }
    else {
      bufp[2] = color;
      bufp[1] = color >> 8;
      bufp[0] = color >> 16;
    }
    }
    break ;

  case 4: { // Probably 32-bpp
    Uint32 *bufp;
    bufp = (Uint32*) g_screenSurface->pixels + y*g_screenSurface->pitch/4 + x;
    *bufp = color;
    }
    break ;
  }
}


static int sign (int v)
{
  if (v < 0) return (-1) ;
  if (v == 0)	return (0) ;
  return (1) ;
}


/* Crude Bressenham algorithm to trace lines without clipping. */
void line (int x1, int y1, int x2, int y2)
{
  int x, y, dx, dy, s1, s2, temp, interchange, i, me ;

  if (SDL_MUSTLOCK (g_screenSurface)) {
    if (SDL_LockSurface(g_screenSurface) < 0) return ;
  }

  x = x1 ;
  y = y1 ;
  dx = abs (x2 - x1) ;
  dy = abs (y2 - y1) ;
  s1 = sign (x2 - x1) ;
  s2 = sign (y2 - y1) ;

  if (dy > dx){
    temp = dx ;
    dx = dy ;
    dy = temp ;
    interchange = 1 ;
	}
  else interchange = 0 ;

  me = 2 * dy - dx ;
  for (i = 0; i < dx; i++) {
    renderPixel (x, y, 0xFF, 0xFF, 0xFF) ;
    while (me >= 0) {
      if (interchange == 1) x = x + s1 ;
      else y = y + s2 ;
      me = me - 2 * dx ;
		}
    if (interchange == 1)	y = y + s2 ;
    else x = x + s1 ;
    me = me + 2 * dy ;
	}

  if (SDL_MUSTLOCK (g_screenSurface))
    SDL_UnlockSurface (g_screenSurface) ;
  SDL_Flip (g_screenSurface) ;
}



void renderCircle (int x0, int y0, int radius, Uint8 R, Uint8 G, Uint8 B)
{
  int x = radius - 1 ;
  int y = 0 ;
  int dx = 1 ;
  int dy = 1 ;
  int err = dx - (radius << 1) ;

  while (x >= y) {
    renderPixel (x0 + x, y0 + y, R, G, B) ;
    renderPixel (x0 + y, y0 + x, R, G, B) ;
    renderPixel (x0 - y, y0 + x, R, G, B) ;
    renderPixel (x0 - x, y0 + y, R, G, B) ;
    renderPixel (x0 - x, y0 - y, R, G, B) ;
    renderPixel (x0 - y, y0 - x, R, G, B) ;
    renderPixel (x0 + y, y0 - x, R, G, B) ;
    renderPixel (x0 + x, y0 - y, R, G, B) ;

    if (err <= 0) {
      y++ ;
      err += dy ;
      dy += 2 ;
    }
    if (err > 0) {
      x-- ;
      dx += 2 ;
      err += (-radius << 1) + dx ;
    }
  }
}
