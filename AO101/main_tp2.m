clear all; %#ok<CLALL>
close ();
clc;

% email du chargé de td : othmane.jerhaoui@ensta-paris.fr

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Méthode GC: Gradient à pas fixe projeté
% Méthode UZAWA: Méthode d'UZAWA
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

EXERCICE = "Exo3";
% EXERCICE = "Exo2";
% EXERCICE = "Exo3";

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Définition des matrices
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

N = 100;
fprintf( "N = %i\n", N );

Mtot = 40;
mi = Mtot / ( N + 2 );
omega = 70 * ( N + 1 );
g0 = 9.81;

x0 = -2;
y0 = 1;
xf = 2;
yf = 1;

J = diag( ones( N - 1, 1 ), 1 );
A = omega * ( 2 * eye( N, N ) - J - J' );
H = [A, zeros( N, N ) ; zeros( N, N ), A];

g = g0 * mi * [zeros( N, 1 ); ones( N, 1 )];
g( 1 ) = -omega * x0;
g( N ) = -omega * xf;
g( N + 1 ) = g( N + 1 ) - omega * y0;
g( 2 * N ) = g( 2 * N ) - omega * yf;

% valeurs propres min et max de la matrice H : 2N x 2N

L1 = min( eig( H ) );
L2N = max( eig( H ) );

eta = 1.e-6;    % residu desiré
Imax = 100000;	% nombre maximal d'iterations

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Réponses par exercice
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

switch EXERCICE
    case "Exo1"
        fprintf( "Résolution par gradient conjugé :\n" );
        zInit = ones( 2 * N, 1 );
        tic;
        [u, n, Residu_u] = GC( H, -g, zInit, eta, Imax );
        t = toc;
        fprintf( "Temps = %5.2f, Itérations : %5i, Résidu : %10.2e\n", t, n, Residu_u( end ) );
        
        xx = [x0; u( 1 : N ); xf];
        yy = [y0; u( N + 1 : 2 * N ); yf];
        
        hold on;
        plot(xx,yy,"r", "Linewidth", 2);
        
    case "Exo2"
        fprintf( "Résolution par gradient projeté :\n" );
        rho = 2 / ( L1 + L2N );
        zInit = ones( 2 * N, 1 );
        r = ( L2N - L1 ) / ( L2N + L1 );
        fprintf( "r := %f\n", r );
        eta2 = ( 1 - r ) / r * eta;
        fprintf( "eta = %5.2e; eta2 = %5.2e\n", eta, eta2 );
        tic;
        [u, n, Norme_diff, Norme_grad] = GP( H, -g, zInit, eta, rho, Imax );
        t = toc;
        fprintf( "Temps = %5.2f, Itérations : %5i, Norme_diff : %10.2e, Norme_grad : %10.2e\n", t, n, Norme_diff, Norme_grad );
        
        xx = [x0; u( 1 : N ); xf];
        yy = [y0; u( N + 1 : 2 * N ); yf];
        
        hold on;
        plot( xx, yy, "r", "Linewidth", 2);
        plot(xx,  0.5*ones(N+2,1), "k", "Linewidth", 2);
        legend( "Solution", "Obstacle" );
        
    case "Exo3"
        C = [0.1 * diag( ones( N, 1 ) ), -diag( ones( N, 1 ) )];
        f =  -0.6 * ones( N, 1 );
        Lambda0 = zeros( N, 1 );
        rho = L1;
        eta = 1.e-3;
        Eps = 1e-5;
        fprintf( "Résolution par méthode d'UZAWA :\n" );
        tic;
        [u, Lambda, n, Residu_Lambda, Residu_u] = UZAWA( H, C, g, f, Lambda0, rho, eta, Eps, Imax );
        t = toc;
        fprintf( "Temps = %5.2f, Itérations : %5i, Résidu : %10.2e\n", t, n, Residu_u( end ) );
        
        xx = [x0; u( 1 : N ); xf];
        yy = [y0; u( N + 1 : 2 * N ); yf];
        
        hold on;
        plot( xx, yy, "r", "Linewidth", 2);
        plot(xx,  0.1 * xx + 0.6, "k", "Linewidth", 2);
        %plot(xx,  0.5*ones(N+2,1), "k", "Linewidth", 2);
        legend( "Solution", "Obstacle" );
end