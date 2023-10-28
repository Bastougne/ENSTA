clear all;
close all
clc;

B = imread( "image.bmp", "bmp" ); % lecture du fichier
B = 255 * B;
image( B );
colormap( gray )

[n, m] = size( B ); % correction par récurrence
C = zeros(n, m);
C(1, :) = B(1, :);
for i = 2 : n - 1 % on cherche le pic de corrélation entre la ligne non-corrigée et la ligne corrigée précédente
    u = C( i - 1, :);
    v = B( i, :);
    r = real( ifft( fft( u ) .* conj( fft( v ) ) ) ); % vecteur des corrélations pour chaque décalage
    [val, j] = max( r ); % décalage maximisant la corrélation entre deux lignes successives
    C( i, :) = circshift( v, j - 1);
end

figure( 2 ); % affichage de l'image corrigée
image( C );
colormap( gray )
imwrite( C, "corr.bmp", "bmp" );