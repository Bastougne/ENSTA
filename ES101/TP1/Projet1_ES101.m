clear all;
close all
clc;
hold on;

[x, Fe] = audioread( "Mo11.wav" ); % lecture du fichier
N = length( x );

X = abs( fft( x ) ); % calcul de la transformée de Fourier
plot( 20 * log10( X ) );

[S, I] = sort( X( 1 : N / 2 ), "descend" ); % récupération des fréquences parasites
f_par = ( I( 1 : 2 ) - 1 ) / N;
plot( I( 1 : 2 ), 20 * log10( S( 1 : 2 ) ), "bx" );

Z = exp( 2i * pi * f_par ); % création du filtre coupe-bande
P = 0.95 * Z;
Num = conv( conv( [1 -Z( 1 )], [1 -Z( 2 )] ), conv( [1 -conj( Z( 1 ) )], [1 -conj( Z( 2 ) )] ) );
Den = conv( conv( [1 -P( 1 )], [1 -P( 2 )] ), conv( [1 -conj( P( 1 ) )], [1 -conj( P( 2 ) )] ) );

figure( 2 ); % filtrage du signal
y = filter( Num, Den, x );
Y = abs( fft( y ) );
plot( 20 * log( Y ) );

audiowrite( "son.wav", y, Fe ); % enregistrement du fichier audio filtré