#include <stdlib.h>
#include "body.h"

/** Integration delta time in seconds. */
#define DT (0.05)



/** Create and register in a linked list a new body. [l] is the linked list
    of bodies where to add this body. The other parameters are the various
    properties of teh body.
    This function return the new head of bodies linked list. */
struct body_list_t* new_body (struct body_list_t* l, int color, int radius,
                              double mass,
                              double x, double y, double vx, double vy)
{
  ////a remplir
  return NULL; //a enlever
}



/** Move a body according to its current acceleration and speed.
    This function updates the [vx], [vy], [x], [y] components. It simply
    integrate acceleration and speed. */
void move_body (struct body_t *b)
{
  ////a remplir
}
