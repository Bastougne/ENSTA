function [u, n, Norme_diff, Norme_grad] = GP( H, b, zInit, eta, rho, Imax )
u = zInit;
Norme_grad = norm( H * u - b );
Norme_diff = 10 * eta; % on doit passer dans la boucle au moins 1 fois
                       % pour que cette norme ait du sens
N = length( zInit ) / 2;
n = 0;
while Norme_diff > eta && n < Imax
    u_avant = u;
    d = H * u - b;
    u = u - rho * d;
    for i = N + 1 : 2 * N
        u( i ) = max( u( i ), 1/2 );
        % La projection sur K est simplement l'application qui met chaque
        % coordonnée verticale à 1/2 si celle-ci est inférieure à 1/2
    end
    Norme_diff = norm( u_avant - u );
    Norme_grad = norm( d );
    n = n + 1;
end
end