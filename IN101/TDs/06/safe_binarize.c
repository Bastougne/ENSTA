#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void my_scanner (FILE *in, char *dest) {
  bool in_comment = false ;
  int read = fgetc (in) ;

  /* Consume and ignore whitespaces and comments */
  while ((read != EOF) &&
         ((read == ' ') || (read == '\n') || read == ('\t') || (in_comment))) {
    if (read == '#') in_comment = true ;
    else {
      if (read == '\n') in_comment = false ;
    }
    read = fgetc (in) ;
  }

  /* If end of file reached without reading a significant character, no more
     job to do. */
  if (read == EOF) {
    dest[0] = '\0' ;
    return ;
  }

  /* We have a significant starting character. Let's go on in the input until
     white space, the end of file or a new comment. */
  dest[0] = read ;
  int i = 1 ;
  read = fgetc (in) ;
  while ((read != EOF) && (read != ' ') && (read != '\n') && read != ('\t')) {
    dest[i] = read ;
    i++ ;
    read = fgetc (in) ;
  }

  if (read == '#') ungetc (read, in) ;
  dest[i] = '\0' ; /* Close the result string. */
}


struct image_t {
  int width ;
  int height ;
  int max_pix_val ;
  int *pixels ;
};


/** Load a PGM image file.
    Set image width, height and max gray-level value by side effect in the
    related paramaters.
    Return the image as an array of integers. */
struct image_t load_pgm (char *fname) {
  char buffer[20] ;
  int size ;
  struct image_t image ;

  /* Set to NULL in case of error. At least, this is done once for all. */
  image.pixels = NULL ;

  FILE *in = fopen (fname, "rb") ;
  if (in == NULL) return image ;

  /* Read the magic number and ensure it is the PGM format's one. */
  my_scanner (in, buffer) ;
  if (strcmp (buffer, "P2") != 0) {
    fclose (in) ;
    return image ;
  }

  /* Read the width, height and gray-level value. */
  my_scanner (in, buffer) ;
  if (buffer[0] == '\0') return image ;
  image.width = atoi (buffer) ;
  my_scanner (in, buffer) ;
  if (buffer[0] == '\0') return image ;
  image.height = atoi (buffer) ;
  my_scanner (in, buffer) ;
  if (buffer[0] == '\0') return image ;
  image.max_pix_val = atoi (buffer) ;

  size = image.width * image.height ;
  /* Ensure the pixels is not empty. */
  if (size <= 0) {
    fclose (in) ;
    return image ;
  }

  /* Allocate memory for the image. */
  int *pixels = malloc (size * sizeof (int)) ;
  if (pixels == NULL) {
    fclose (in) ;
    return image ;
  }

  /* Read the bytes of the image. */
  for (int i = 0; i < size; i++) {
    my_scanner (in, buffer) ;
    if (buffer[0] == '\0') {
      fclose (in) ;
      free (pixels) ;
      return image ;
    }
    pixels[i] = atoi (buffer) ;
  }

  /* Cleanup. */
  fclose (in) ;
  image.pixels = pixels ;
  return image ;
}



bool save_pgm (char *fname, struct image_t image) {

  if (image.pixels == NULL) return false ;

  FILE *out = fopen (fname, "wb") ;
  if (out == NULL) return (false) ;

  fprintf
    (out, "P2\n%d\n%d\n%d\n", image.width, image.height, image.max_pix_val) ;
  int size = image.width * image.height ;

  int *pixels = image.pixels ;
  for (int i = 0; i < size; i++) fprintf (out, "%d\n", pixels[i]) ;
  fclose (out) ;
  return (true) ;
}



void binarize_pgm (int thresh, struct image_t *image) {
  if (image->pixels == NULL) return ;

  int  size = image->width * image->height ;
  int *pixels = image->pixels ;
  for (int i = 0; i < size; i++) {
    /* 2 colors : 0 -> black, 1 -> white. */
    if (pixels[i] < thresh) pixels[i] = 0 ;
    else pixels[i] = 1 ;
  }
  /* Two colors => max intensity level is 1. */
  image->max_pix_val = 1 ;
}



int main (int argc, char *argv[]) {
  int thresh ;
  bool err_code ;

  if (argc != 4) {
    printf ("Error. Usage: binarize.x img-source img-dest threshold\n") ;
    return 1 ;
  }

  /* Load image. */
  struct image_t image = load_pgm (argv[1]) ;
  if (image.pixels == NULL) {
    printf ("Error. Unable to load image.\n") ;
    return 1 ;
  }

  /* Get the threshold. */
  thresh = atoi (argv[3]) ;
  /* Simple 3-rule. */
  thresh = (image.max_pix_val * thresh) / 255 ;

  /* Convert to black and white. */
  binarize_pgm (thresh, &image) ;

  /* Save image. Its max_pix_val is now 1 since we have only 2 colors. */
  err_code = save_pgm (argv[2], image) ;
  if (! err_code) {
    printf ("Error. Unable to save image.\n") ;
    return 1 ;
  }

  /* Free the pixels of the image. */
  free (image.pixels) ;
  return 0 ;
}
