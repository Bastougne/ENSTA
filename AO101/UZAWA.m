function [u, Lambda, n, Residu_Lambda, Residu_u] = UZAWA( H, C, g, f, Lambda0, rho, eta, Eps, Imax )
Lambda = Lambda0;
u = -H \ ( C' * Lambda + g );
Residu_Lambda = norm( max( 0, C * u - f ) );
Residu_u = 10 * eta;
n = 0;
while ( Residu_Lambda > eta || Residu_u > Eps ) && n < Imax
    Lambda = max( 0, Lambda + rho * ( C * u - f ) );
    u_avant = u;
    u = -H \ ( C' * Lambda + g );
    Residu_Lambda = norm( max( 0, C * u - f ) );
    Residu_u = norm( u_avant - u );
    n = n + 1;
end
end