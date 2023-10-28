clear all;
close all
clc;

[x1, Fe] = audioread( "Erlk.wav" ); % lecture du fichier
N = length( x1 );

teta = [0 : pi / ( N - 1 ) : pi]; % création de l'effet stéréo
tau = ( 0.15 * sin( teta ) ) / 340;
x2 = zeros (N ,1) ;
for i = 1 : N
    if round( tau(i) * Fe ) < i
        x2(i) = x1( i - round( tau(i) * Fe ) );
    else
        x2(i) = 0;
    end
end
y = [x1 x2];
audiowrite( "resultat.wav", y, Fe ); % enregistrement du fichier stéréo