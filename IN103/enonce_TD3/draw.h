#ifndef __DRAW_H__
#define __DRAW_H__

#include "body.h"

/** Size of the drawing window. */
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

/** Draw or clear all the bodies. If [clear] is false then bodies are drawn
    with their color, otherwise they are dranw black, i.e. erased from the
    screen. */
void draw_bodies (bool clear, struct body_list_t *bl) ;

#endif
