#include <stdio.h>
#include <stdbool.h>
#include "station.h"
#include "load_map.h"
#include "utils.h"
#include "search.h"


int main (int argc, char *argv[])
{
  char src_name[256], dest_name[256] ;
  struct station_t *src, *dest ;
  bool found ;

  if (argc != 2) {
    printf ("Error. Missing railway network description file.\n") ;
    return (1) ;
  }

  load_map (argv[1]) ;
  printf ("------------------------------------------------------------\n") ;
  print_stations (get_all_stations ()) ;
  printf ("------------------------------------------------------------\n") ;
  printf ("Source station: ") ;
  gets (src_name) ;
  printf ("Target station: ") ;
  gets (dest_name) ;

  /* Recherche de la station de départ. */
  src = find_station (src_name) ;
  if (src == NULL) {
    printf ("Source station '%s' not found.\n", src_name) ;
    return (1) ;
  }

  /* Recherche de la station d'arrivée. */
  dest = find_station (dest_name) ;
  if (dest == NULL) {
    printf ("Target station '%s' not found.\n", dest_name) ;
    return (1) ;
  }

  /* Attention, à chaque recherche, il faut dire que la station de départ
     n'a pas de prédécesseur dans le chemin que l'on trouvera. */
  src->prev_in_path = NULL ;
  /* Recherche de l'existence d'un chemin entre les 2, en faisant un parcours
     menant au plus court chemin. */
  found = shortest_path (src, dest) ;
  if (found) {
    printf ("Found\n") ;
    print_shortest_path_reversed (dest) ;
  }
  else printf ("Not found.\n") ;

  return (0) ;
}
