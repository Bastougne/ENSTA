#include <stdio.h>

#include "paint.c"

void ligne_horizontale( int j, int i_min, int i_max, int r, int g, int b, int largeur, int hauteur, unsigned char *pixels ) {
    for ( int i = i_min; i <= i_max; ++i ) {
        color_pixel( i, j, r, g, b, largeur, hauteur, pixels );
    }
}

int main() {
    int largeur = 600;
    int hauteur = 400;
    int j = 50;
    int i_min = 100;
    int i_max = 500;
    // Creer les pixels pour dessiner
    unsigned char *pixels = create_pixels( largeur, hauteur );

    unsigned char r, g, b;

    // couleur rouge
    r = 255;
    g = 0;
    b = 0;

    ligne_horizontale( j, i_min, i_max, r, g, b, largeur, hauteur, pixels );

    /* Ecrire vers un fichier BMP */
    save_BMP( "ligne.bmp", largeur, hauteur, pixels );

    /* Détruire le canvas pour libérer la mémoire */
    destroy_pixels( pixels );

    return ( 0 );
}