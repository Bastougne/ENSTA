#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "paint.h"


void fill (int width, int height, int nb_init,unsigned char* pixels)
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
  for ( i = 0; i < nb_init; i++ ) {
      struct point_info_t point; // On définit un nouveau point
      point.x = rand() % width;
      point.y = rand() % height;
      point.r = rand() % 256;
      point.g = rand() % 256;
      point.b = rand() % 256;
      processed[point.x + point.y * width] = true;
      enqueue( q, point ); // Le nouveau point est ajouté à la file

      init_points[i].x = point.x; // Les points initiaux sont en noir
      init_points[i].y = point.y;
      init_points[i].r = 0;
      init_points[i].g = 0;
      init_points[i].b = 0;
  }
  while ( is_empty( q ) == false ) {
    struct point_info_t point = take( q );
    int x = point.x;
    int y = point.y;
    color_pixel( x, point.y, point.r, point.g, point.b, width, height, pixels );
    for ( int m = -1; m < 2; m++ ) { // Ceci permet de parcourir les points voisins
      for ( int n = -1; n < 2; n++ ) {
        if ( x + m > 0 && x + m < width && y + n > 0 && y + n < height ) { // On vérifie si on est dans le cadre
          if ( processed[x + m + ( y + n ) * width] == false ) { // Si le point n'a pas déjà été évalué, on l'ajoute dans la file
            point.x = x + m;
            point.y = y + n;
            processed[ x + m + ( y + n ) * width] = true;
            enqueue( q, point );
          }
        }
      }
    }
  }
  queue_free (q) ;
  free (processed) ;
  for (i = 0; i < nb_init; i++) 
    color_pixel(init_points[i].x, init_points[i].y, init_points[i].r, init_points[i].g, init_points[i].b, width, height, pixels);
  free (init_points) ;
}