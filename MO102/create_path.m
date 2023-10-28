% test bruit gaussien

clear;
close all;
clc;

debut = 0;
fin = 10;
valeurs = 20;
t = linspace( debut, fin, valeurs );

% def bords terrain, nb amers
% def arc de visibilté

X = sin( t ) + 0.2 * randn( 1, valeurs );
Y = t .* cos( t ) + 0.2 * randn( 1, valeurs );

plot( X, Y );
