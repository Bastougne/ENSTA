clear;
close all;
clc;

load( "filtreKalman.mat" );
F = [1, T, 0, 0; 0, 1, 0, 0; 0, 0, 1, T; 0, 0, 0, 1];
H = [1, 0, 0, 0; 0, 0, 1, 0];
W = T * diag( [sigma_p^2, sigma_v^2, sigma_p^2, sigma_v^2] );
V = sigma_z^2 * eye( 2 );

X_plot = zeros( 4, N );
X_c = zeros( 4, 1 );
P_c = 1000 * eye( 4 );
Trace = zeros( 1, N );

for k = 0 : N - 1
   X_p = F * X_c;
   P_p = F * P_c * F' + W;

   K = P_p * H' / ( H * P_p * H' + V );
   X_c = X_p + K * ( Z( :, k + 1 ) - H * X_p );
   P_c = P_p - K * H * P_p;
   
   X_plot( :, k + 1 ) = X_c;
   Trace( 1, k + 1 ) = trace( P_c );
end

for k = 1 : 4
    figure( k );
    hold on;
    plot( X_plot( k, : ), 'k' );
    plot( X( k, : ), 'b--' );
end
figure( 5 );
plot( Trace );

