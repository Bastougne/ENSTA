#include <stdio.h>

#include "paint.c"

void rectangle( int j_min, int j_max, int i_min, int i_max, int r, int g, int b,
                int largeur, int hauteur, unsigned char *pixels ) {
    for ( int i = i_min; i <= i_max; ++i ) {
        for ( int j = j_min; j <= j_max; ++j ) {
            color_pixel( i, j, r, g, b, largeur, hauteur, pixels );
        }
    }
}

int main() {
    int largeur = 600;
    int hauteur = 400;
    int j_min = 100;
    int j_max = 250;
    int i_min = 50;
    int i_max = 500; // Creer les pixels pour dessiner
    unsigned char *pixels = create_pixels( largeur, hauteur );

    unsigned char r, g, b;

    // couleur rouge
    r = 255;
    g = 0;
    b = 0;

    rectangle( j_min, j_max, i_min, i_max, r, g, b, largeur, hauteur, pixels );

    /* Ecrire vers un fichier BMP */
    save_BMP( "rectangle.bmp", largeur, hauteur, pixels );

    /* Détruire le canvas pour libérer la mémoire */
    destroy_pixels( pixels );

    return ( 0 );
}