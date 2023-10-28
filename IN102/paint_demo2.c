#include <stdio.h>

#include "paint.c"

int main() {
    int largeur = 600;
    int hauteur = 400;

    // Creer les pixels pour dessiner
    unsigned char *pixels = create_pixels( largeur, hauteur );

    unsigned char r, g, b;

    // couleur rouge
    r = 255;
    g = 0;
    b = 0;
    // Colorier le pixel (5,10) à (9,10)
    for ( int k = 100; k <= 500; ++k ) {
        color_pixel( k, 50, r, g, b, largeur, hauteur, pixels );
    }

    /* Ecrire vers un fichier BMP */
    save_BMP( "ligne.bmp", largeur, hauteur, pixels );

    /* Détruire le canvas pour libérer la mémoire */
    destroy_pixels( pixels );

    return ( 0 );
}
