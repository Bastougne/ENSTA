#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "gfxprims.h"
#include "queue.h"



void fill (int width, int height, int nb_init)
{
  int i ;
  bool *processed ;
  struct queue_t *q ;
  struct point_info_t *init_points ;

  /* Allocation de la file. Taille max: width * height. */
  q = queue_alloc (width * height) ;
  if (q == NULL) {
    printf ("No mem for queue.\n") ;
    return ;
  }

  /* Allocation du tableau pour se souvenir des points initiaux et redessiner
     par dessus en noir à la fin. */
  init_points = malloc (nb_init * sizeof (struct point_info_t)) ;
  if (init_points == NULL) {
    printf ("Nom mem for initial points.\n") ;
    queue_free (q) ;
    return ;
  }

  /* Allocation du tableau disant si un point a déjà été mis en file. */
  processed = malloc (width * height * sizeof (bool)) ;
  if (processed == NULL) {
    printf ("No mem for processed array.\n") ;
    free (init_points) ;
    queue_free (q) ;
    return ;
  }
  /* Au début, aucun point n'a déjà été traité. */
  for (i = 0; i < width * height; i++) processed[i] = false ;

  /* Choix des points de départ avec des coordonnées et des couleurs
     aléatoires. */
  for (i = 0; i < nb_init; i++) {
    struct point_info_t pi ;

    pi.x = rand () % width ;
    pi.y = rand () % height ;
    pi.r = rand () % 256 ;
    pi.g = rand () % 256 ;
    pi.b = rand () % 256 ;
    enqueue (q, pi) ;
    /* Marquer le point comme traité. */
    processed[(pi.y * width) + pi.x] = true ;

    init_points[i].x = pi.x ;
    init_points[i].y = pi.y ;
    init_points[i].r = 0 ;
    init_points[i].g = 0  ;
    init_points[i].b = 0  ;
  }

  /* Tant que la file n'est pas vide... */
  while (! is_empty (q)) {
    int xm1, x, xp1, ym1, y, yp1 ;
    /* On extrait un élément. */
    struct point_info_t pi = take (q) ;

    /* On on affiche le point avec sa couleur. */
    renderPixel (pi.x, pi.y, pi.r, pi.g, pi.b) ;
    /* Pour chaque voisin 3x3 qui n'est pas en dehors de l'écran, on le
       met dans la file avec la même couleur que le point courant. */
    xm1 = pi.x - 1 ;
    x = pi.x ;
    xp1 = pi.x + 1 ;
    ym1 = pi.y - 1 ;
    y = pi.y ;
    yp1 = pi.y + 1 ;

    /* Voisins sur la ligne d'ordonnée précédente. */
    if (ym1 >= 0) {
      /* Ordonnée ligne précédente valide. */
      if (xm1 >= 0) {
        /* enqueue xm1, ym1. */
        if (! processed[(ym1 * width) + xm1]) {
          pi.x = xm1 ; pi.y = ym1 ; enqueue (q, pi) ;
          processed[(ym1 * width) + xm1] = true ;
        }
      }
      /* enqueue x, ym1. */
      if (! processed[(ym1 * width) + x]) {
        pi.x = x ; pi.y = ym1 ; enqueue (q, pi) ;
        processed[(ym1 * width) + x] = true ;
      }
      if (xp1 < width) {
        /* enqueue (xp1, ym1). */
        if (! processed[(ym1 * width) + xp1]) {
          pi.x = xp1 ; pi.y = ym1 ; enqueue (q, pi) ;
          processed[(ym1 * width) + xp1] = true ;
        }
      }
    }   /* Fin de if (ym1 >= 0). */

    /* Voisins à la même ordonnée que le point courant. */
    if (xm1 >= 0) {
      /* enqueue xm1, y. */
      if (! processed[(y * width) + xm1]) {
        pi.x = xm1 ; pi.y = y ; enqueue (q, pi) ;
        processed[(y * width) + xm1] = true ;
      }
    }
    if (xp1 < width) {
      /* enqueue (xp1, y). */
      if (! processed[(y * width) + xp1]) {
        pi.x = xp1 ; pi.y = y ; enqueue (q, pi) ;
        processed[(y * width) + xp1] = true ;
      }
    }

    /* Voisins sur la ligne d'ordonnée suivante. */
    if (yp1 < height) {
      /* Ordonnée ligne suivante valide. */
      if (xm1 >= 0) {
        /* enqueue xm1, yp1. */
        if (! processed[(yp1 * width) + xm1]) {
          pi.x = xm1 ; pi.y = yp1 ; enqueue (q, pi) ;
          processed[(yp1 * width) + xm1] = true ;
        }
      }
      /* enqueue x, yp1. */
      if (! processed[(yp1 * width) + x]) {
        pi.x = x ; pi.y = yp1 ; enqueue (q, pi) ;
        processed[(yp1 * width) + x] = true ;
      }
      if (xp1 < width) {
        /* enqueue (xp1, yp1). */
        if (! processed[(yp1 * width) + xp1]) {
          pi.x = xp1 ; pi.y = yp1 ; enqueue (q, pi) ;
          processed[(yp1 * width) + xp1] = true ;
        }
      }
    }  /* Fin de if (yp1 < height). */
  }  /* Fin de while (! is_empty (q)). */

  queue_free (q) ;
  free (processed) ;

  for (i = 0; i < nb_init; i++)
    renderPixel (init_points[i].x, init_points[i].y,
                 init_points[i].r, init_points[i].g, init_points[i].b) ;
  free (init_points) ;
}
