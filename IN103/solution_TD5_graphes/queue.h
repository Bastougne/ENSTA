#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdbool.h>
#include "station.h"

struct queue_t {
  unsigned int max_nb ;      /* Nombre max d'éléments. */
  unsigned int cur_nb ;      /* Nombre actuel d'éléments. */
  unsigned int first ;       /* Indice du premier élément. */
  struct station_t **data ;
};

struct queue_t* queue_alloc (unsigned int max_size) ;
void queue_free (struct queue_t *q) ;
struct station_t* take (struct queue_t *q) ;
void enqueue (struct queue_t *q, struct station_t *pi) ;
bool is_empty (struct queue_t *q) ;
#endif
