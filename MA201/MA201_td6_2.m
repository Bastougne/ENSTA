clear;
close all;
clc;

load( "algoEM.mat" );
M = 10;
P1 = zeros( n, M );
P2 = zeros( n, M );

for m = 2 : M - 1
    for i = 1 : n
        val1 = f( x( i ), mu1, sigma1 ) * lambda;
        val2 = f( x( i ), mu2, sigma2 ) * ( 1 - lambda );
        P1( i, m ) = val1 / ( val1 + val2 );
        P2( i, m ) = val2 / ( val1 + val2 );
    end

    lambda = mean( P1( :, m );
    mu1 = à
end

function p = f( x, mu, sigma )
    p = ( 2 * pi * mu^2 )^-0.5 * exp( - ( x - mu )^2 / ( 2 * sigma^2 ) );
end
