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
  for (int k = 0; k < nb_init; k++) {
      struct point_info point;
      point.x = rand() % width;
      point.y = rand() % height;
      point.r = rand() % 256;
      point.g = rand() % 256;
      point.b = rand() % 256;
      init_points[i].x = point.x;
      init_points[i].y = point.y;
      init_points[i].r = 0;
      init_points[i].g = 0;
      init_points[i].b = 0;
  }



  queue_free (q) ;
  free (processed) ;

  for (i = 0; i < nb_init; i++)
    color_pixel(init_points[i].x, init_points[i].y,
                 init_points[i].r, init_points[i].g, init_points[i].b, width, height, pixels);
    
  free (init_points) ;
}
