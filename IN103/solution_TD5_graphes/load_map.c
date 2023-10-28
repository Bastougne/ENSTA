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
  bool end ;
  FILE *in ;
  char *read ;
  char buffer[256] ;
  struct station_t *prev_station ;

  in = fopen (name, "rb") ;
  if (in == NULL) return (false) ;

  /* NOTE: since I *really* want to assign [read] then test its value, I use
     a = in the test. To prevent the compiler from generating a warning, I
     explicitely surrounded the expression by ().
     Hence wo *do* need this double-layer of parentheses. */
  while ((read = fgets (buffer, 255, in))) {
    /* Première chaîne: supposée nom de ligne. */
    // printf ("Found line: %s\n", buffer) ;
    prev_station = NULL ;

    /* Lecture des stations jusqu'à un ".". */
    end = false ;
    while ((read = fgets (buffer, 255, in)) && (! end)) {
      unsigned int len = strlen (buffer) ;
      /* On retire l'éventuel retour à la ligne happé par fgets (). */
      if (buffer[len - 1] == '\n') (buffer[len - 1] = '\0') ;
      /* On vérifie si on a atteint une fin de ligne de métro. */
      if (strcmp (buffer, ".") == 0) {
        // printf ("End of line.\n") ;
        end = true ;
      }
      else {
        /* Nom de station trouvé. */
        struct station_t *new_station = get_or_create_station (buffer) ;
        /* Si on n'est pas la première station de la ligne... */
        if (prev_station != NULL) {
          /* On se rajoute comme voisin de la station précédente. */
          struct stations_list_t *lst =
            malloc (sizeof (struct stations_list_t)) ;
          lst->station = new_station ;
          /* On ajoute le voisin en tête de la liste de voisins. */
          lst->next = prev_station->neighbours ;
          prev_station->neighbours = lst ;
          /* On rajoute la station précédente comme voisin de nous-même. */
          lst = malloc (sizeof (struct stations_list_t)) ;
          lst->station = prev_station ;
          lst->next = new_station->neighbours ;
          new_station->neighbours = lst ;
        }

        prev_station = new_station ;
      }
    }
  }

  fclose (in) ;
  return (true) ;
}
