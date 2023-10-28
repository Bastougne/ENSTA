#include <stdlib.h>

#include "body.h"
#include "simu.h"


/** A simple constant force. It does not depend on the position or speed.
    The coordinates of the computed force are returned by address in
    [fx] and [fy]. */
void f (double x, double y, double vx, double vy, double *fx, double *fy)
{
  *fx = 5.0 ;
  *fy = 5.0 ;
}



/** The array containing all the forces to apply to bodies. It must be
    NULL-terminated.
    We could imagine that all the forces do not apply on all the objects.
    In this case, make several arrays or link objects and forces. */
force_t forces_array[] = { f, NULL } ;






/** Apply all the forces of tha array [forces] onto the body [b]. This function
    simply update the acceleration from the applied force, the current
    acceleration of the body and its mass. It's indeed the second Newton's
    law. */
void apply_forces_on_body (struct body_t *b, force_t *forces)
{
  unsigned int i = 0 ;

  /* Scan the array of forces up to its end. */
  while (forces[i] != NULL) {
    double fx, fy ;

    /* Apply the force by calling the force-function, depending on the body's
       position and speed. */
    (forces[i]) (b->x, b->y, b->vx, b->vy, &fx, &fy) ;
    /* Update the body's acceleration to reflect the force's effect. */
    b->ax = b->ax + fx / b->mass ;
    b->ay= b->ay + fy / b->mass ;
    /* Going to the next force if any. */
    i++ ;
  }
}



/** Run all the forces on all the bodies. Add the gravity as a shortcut
    by setting the initial y acceleration to 1g. This is simpler than computing
    the force induced between the Earth and each object, then apply this force
    to compute the acceleration. */
void simulate_bodies (struct body_list_t *bl, force_t *forces)
{
  while (bl != NULL) {
    struct body_t *b = bl->body ;

    /* Clear the x acceleration and initialize y with the gravity. */
    b->ax = 0.0 ;
    b->ay = -9.81 ;
    /* Apply all the forces on this body. */
    apply_forces_on_body (b, forces) ;
    /* Update speed and position. */
    move_body (b) ;

    bl = bl->next ;
  }
}
