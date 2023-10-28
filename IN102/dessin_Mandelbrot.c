#include <math.h>
#include <stdio.h>

#include "paint.c"

int compter_iteration( double x, double y, int max_iter ) {
    double a = 0;
    double b = 0;
    double c = 0;
    int n = 0;
    while ( a * a + b * b <= 2 && n < max_iter ) {
        c = a * b;
        a = a * a - b * b + x;
        b = 2 * c + y;
        n = n + 1;
    }
    return ( n );
}

void Mandelbrot( int width, int height, double x_left, double y_top, double x_width, double y_height, int max_iter, unsigned char *pixels ) {
    for ( double i = 0; i < width; i = i + 1.0 ) {
        for ( double j = 0; j < height; j = j + 1.0 ) {
            double x = x_left + ( i / width ) * x_width;
            double y = y_top - ( j / height ) * y_height;
            int n = compter_iteration( x, y, max_iter );
            int r = 255 * n / max_iter;
            int b = 255 - r;
            if ( n == max_iter ) {
                color_pixel( i, j, 0, 0, 0, width, height, pixels );
            } else {
                color_pixel( i, j, r, 0, b, width, height, pixels );
            }
        }
    }
}

int main() {
    int width = 600;
    int height = 400;
    double x_left = -2.0;
    double y_top = 1.0;
    double x_width = 3.0;
    double y_height = x_width * height / width;
    int max_iter = 100;
    unsigned char *pixels = create_pixels( width, height );

    Mandelbrot( width, height, x_left, y_top, x_width, y_height, max_iter, pixels );
    save_BMP( "Mandelbrot.bmp", width, height, pixels );
    destroy_pixels( pixels );

    return ( 0 );
}