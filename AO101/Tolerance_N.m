N = 10000;
X = 1 : N;
gamma = zeros( N, 1 );
eta = zeros( N, 1 );
for i = 1 : N
    alpha = pi / ( 2 * i + 2 );
    gamma( i ) = 2 * cos( alpha )^2 - 1;
    eta( i ) = 2 * sin( alpha )^2 / gamma( i );
end
%semilogx( X, gamma, "k", "Linewidth", 2);
semilogx( X( 2 : end ), eta( 2 : end ), "k", "Linewidth", 2);