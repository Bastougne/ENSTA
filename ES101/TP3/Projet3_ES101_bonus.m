clear all;
close all
clc;
hold on;

[x, Fe] = audioread( "Encode.wav" ); % lecture du fichier
N = length( x );

X = abs( fft( x ) ); % calcul de la transformée de Fourier
plot( 20 * log10( X ) );

