#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station.h"
#include "load_map.h"
#include "utils.h"


void print_stations (struct stations_list_t *stations)
{
  struct stations_list_t *neighbours ;

  while (stations != NULL) {
    printf ("Station: %s\n", stations->station->name) ;
    printf ("Voisins: ") ;
    neighbours = stations->station->neighbours ;
    while (neighbours != NULL) {
      printf ("%s ", neighbours->station->name) ;
      neighbours = neighbours->next ;
    }
    printf ("\n") ;
    stations = stations->next ;
  }
}



struct station_t* find_station (char *name)
{
  struct stations_list_t *stations = get_all_stations () ;
  while (stations != NULL) {
    if (strcmp (stations->station->name, name) == 0)
      return (stations->station) ;
    stations = stations->next ;
  }
  return (NULL) ;
}
