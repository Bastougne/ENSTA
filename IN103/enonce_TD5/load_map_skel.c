#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station.h"



static unsigned int nb_stations = 0 ;
static struct stations_list_t *all_stations = NULL ;


static struct station_t* get_or_create_station (char *name)
{
  struct stations_list_t *list_cell ;
  struct station_t *st ;

  /* On commence par rechercher si la stations n'existerait pas déjà. */
  struct stations_list_t *stations = all_stations ;
  while (stations != NULL) {
    if (strcmp (stations->station->name, name) == 0)
      return (stations->station) ;
    stations = stations->next ;
  }

  /* Si on arrive ici, c'est qu'on n'a pas trouvé un noeud déjà
     existant. On va le créer. */
  st = malloc (sizeof (struct station_t)) ;
  st->name = malloc ((1 + strlen (name)) * sizeof (char)) ;
  st->seen = false ;
  strcpy (st->name, name) ;
  st->neighbours = NULL ;

  /* On rajoute le noeud en tête de la liste de toutes les stations. */
  list_cell = malloc (sizeof (struct stations_list_t)) ;
  list_cell->station = st ;
  list_cell->next = all_stations ;
  all_stations = list_cell ;
  /* Une station de plus de créée. */
  nb_stations++ ;
  return (st) ;
}



/** \brief Retourne le pointeur sur la tête de la liste chaînée de stations
    construites. */
struct stations_list_t* get_all_stations ()
{
  return (all_stations) ;
}



bool load_map (char *name)
{
  /* ********** FILL HERE ********** */
}

