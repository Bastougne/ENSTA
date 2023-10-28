#ifndef __BODY_H__
#define __BODY_H__

/** Structure of a body. */
struct body_t {
  int color ;      /** Drawing color. */
  int radius ;     /** Radius of the circle used to draw the body. */
  double mass ;    /** Mass in Kg. */
  double x, y ;    /** 2D coordinates. */
  double vx, vy ;  /** 2D speed. */
  double ax, ay ;  /** 2D acceleration. */
} ;


/** Linked list of bodies. */
struct body_list_t {
  struct body_t *body ;
  struct body_list_t *next ;
} ;

/** Create and register in a linked list a new body. [l] is the linked list
    of bodies where to add this body. The other parameters are the various
    properties of teh body.
    This function return the new head of bodies linked list. */
struct body_list_t* new_body (struct body_list_t* l, int color, int radius,
                              double mass,
                              double x, double y, double vx, double vy) ;

/** Move a body according to its current acceleration and speed.
    This function updates the [vx], [vy], [x], [y] components. It simply
    integrate acceleration and speed. */
void move_body (struct body_t *b) ;
#endif
