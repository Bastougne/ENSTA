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
  struct body_list_t *new_cell ;
  struct body_t *b = malloc (sizeof (struct body_t)) ;
  if (b == NULL) return (NULL) ;

  /* Allocate a new linked list cell. */
  new_cell= malloc (sizeof (struct body_list_t)) ;
  if (new_cell == NULL) {
    free (b) ;   /* Free the successfully allocated body. */
    return (NULL) ;
  }

  /* Initialize the body. */
  b->color = color ;
  b->radius = radius ;
  b->mass = mass ;
  b->x = x ; b->y = y ;
  b->vx = vx ; b->vy = vy ;
  b->ax = 0.0 ; b->ay = 0.0 ;

  /* Link the body in the list. */
  new_cell->body = b ;
  new_cell->next = l ;

  return (new_cell) ;
}



/** Move a body according to its current acceleration and speed.
    This function updates the [vx], [vy], [x], [y] components. It simply
    integrate acceleration and speed. */
void move_body (struct body_t *b)
{
  /* Update speed from acceleration. */
  b->vx = b->vx + b->ax * DT ;
  b->vy = b->vy + b->ay * DT ;
  /* Update position from speed. */
  b->x = b->x + b->vx * DT ;
  b->y = b->y + b->vy * DT ;
}
