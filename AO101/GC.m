function [u, n, Residu_u] = GC( H, b, zInit, eta, Imax )
u = zInit;
g = H * u - b;
d = -g;
n = 0;
Residu_u = norm( H * u - b );
while Residu_u > eta && n < Imax
    rho = ( g' * g ) / ( d' * H' * d );
    u = u + rho * d;
    g_avant = g;
    g = H * u - b;
    beta = ( norm( g ) / norm( g_avant ) )^2;
    d = -g + beta * d;
    Residu_u = norm( H * u - b );
    n = n + 1;
end
end