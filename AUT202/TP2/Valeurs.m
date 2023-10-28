J = 0.02
m = 0.6
sigma = 0.8
g = 9.81

A = [0          , 1, 0                 , 0;
     0          , 0, -g / ( 1 + sigma ), 0;
     0          , 0, 0                 , 1;
     - m * g / J, 0, 0                 , 0]

 B = [0; 0; 0; 1 / J]

omega = ( ( m * g^2 ) / ( ( 1 + sigma ) * J ) )^(1/4)

P_K = [-omega, -2 * omega, ( -1 + 1i ) * omega, -( 1 + 1i ) * omega]
K1 = place( A, B, P_K )

R = eye(4)
Q = eye(1)
N = zeros(4,1)

[K, S, e_K] = lqr( A, B, R, Q, N )

C = [1, 0, 0, 0;
     0, 0, 1, 0];

P_L = [-omega, -3 * omega, ( -2 + 1i ) * omega, -( 2 + 1i ) * omega]
L = place( A', C', P_L )'

e_L = eig( A - L * C )

init = [0.1; 0; 0; 0]

