#ifndef __SIMU_H__
#define __SIMU_H__

#include "body.h"

/** Type alias for functions computing forces. */
typedef void (*force_t) (double, double, double, double, double*, double*) ;

extern force_t forces_array[] ;
void apply_forces_on_body (struct body_t *b, force_t *forces) ;
void simulate_bodies (struct body_list_t *bl, force_t *forces) ;

#endif
