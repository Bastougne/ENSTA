% réinitialiser l'environnement
clear;
close all;
clc;
%#ok<*SAGROW> % masque les avertissements de redimensionnement

% --- NE RIEN MODIFIER HORS DE CETTE ZONE ---

% constantes ajustables
Nmax = 20; % nombre maximum de perceptions simultannées
erreur = 3; % erreur en position initiale du robot
coef = 0.2; % coefficient de proportionnalité des covariances
seuil = 3; % intervalle de confiance pour la correspondance des amers ( 1 => 68,3%, 2 => 95,5%, 3 = 99,7% )

% ouvrir le fichier
addpath( genpath( 'C:\Users\hbast\Documents\MATLAB\Kalman' ) );
FileID = fopen( 'C:\Users\hbast\Documents\MATLAB\Kalman\in\PartialObservation.txt' );

% paramètres de l'enregistrement vidéo
video = VideoWriter( 'C:\Users\hbast\Documents\MATLAB\Kalman\out\PartialObservation.avi', 'Motion JPEG AVI' );
video.FrameRate = 2;
video.Quality = 100;

% --- NE RIEN MODIFIER HORS DE CETTE ZONE ---

% lire la première ligne
format = strcat( 'percep :', repmat( ' %f', 1, 2 * Nmax ) );
Y = cell2mat( textscan( FileID, format, 'EmptyValue', NaN ) )';
[GC, GR] = groupcounts( Y );
if isnan( GR( end ) )
    Y = Y( 1 : 2 * Nmax - GC( end ) );
end

% initialiser les variables du filtre
X = [0; 0; Y];
P = zeros( length( X ), length( X ) ); % covariance de Y
P( 1 : 2, 1 : 2 ) = erreur * eye( 2 );
for i = 3 : 2 : length( X )
    P( i : i + 1, i : i + 1 ) = coef * norm( Y( i - 2 : i - 1, 1 ) ) * eye( 2 );
end
B = [eye( 2 ); zeros( length( Y ), 2 )];

% afficher la carte et enregistrer
axis equal;
hold on;
plot( X( 1 ), X( 2 ), 'bs' );
viscircles( [X( 1 ), X( 2 )], P( 1, 1 ), 'Color', 'b', 'LineWidth', 0.3, 'LineStyle', ':' );
for i = 3 : 2 : length( Y ) + 2
    plot( X( i ), X( i + 1 ), 'rx' );
    viscircles( [X( i ) X( i + 1 )], P( i, i ), 'Color', 'r', 'LineWidth', 0.5 );
end
Pred_x = X( 1 );
Pred_y = X( 2 );
Corr_x = X( 1 );
Corr_y = X( 2 );
open( video );
writeVideo( video, getframe( gcf ) );

% tant que le fichier n'est pas vide
while ~feof( FileID ) == 1
    clf;
    axis equal;
    hold on;
    
    % lire une odométrie
    u = cell2mat( textscan( FileID, 'odom : %f %f' ) )';
    
    % effectuer la prédiction de l'état
    Q = coef * norm( u ) * eye( 2 ); % covariance de u
    Xs = X + B * u;
    Ps = P + B * Q * B';
    
    % lire une perception
    Y = cell2mat( textscan( FileID, format, 'EmptyValue', NaN ) )';
    [GC, GR] = groupcounts( Y );
    if isnan( GR( end ) )
        Y = Y( 1 : 2 * Nmax - GC( end ) );
    end
    
    % analyser l'observation partielle
    H = zeros( 0, length( Xs ) );
    Y_known = zeros( 0, 1 );
    Y_new = zeros( 0, 0 );
    Vu = zeros( length( Xs ) / 2 );
    for i = 1 : 2 : length( Y )
        j_min = 1; % recherche de l'amer connu le plus proche de l'amer observé j
        d_min = norm( Xs( 3 : 4, 1 ) - Xs( 1 : 2, 1 ) - Y( i : i + 1, 1 ) ) / Ps( 3, 3 );
        for j = 1 : 2 : length( Xs ) - 2
            d = norm( Xs( j + 2 : j + 3, 1 ) - Xs( 1 : 2, 1 ) - Y( i : i + 1, 1 ) ) / Ps( j + 2, j + 2 );
            if d < d_min
                d_min = d;
                j_min = j;
            end
        end
        if d_min < seuil % critère de validité pour la correspondance
            Y_known( end + 1 : end + 2, 1 ) = Y( i : i + 1, 1 );
            H( end + 1 : end + 2, 1 : 2 ) = -1 * eye( 2 );
            H( end - 1 : end, j_min + 2 : j_min + 3 ) = eye( 2 );
            Vu( j_min ) = 1;
        else
            Y_new( end + 1 : end + 2, 1 ) = Y( i : i + 1, 1 );
        end
    end
    
    % effectuer la prédiction de l'observation
    Ys = H * Xs;
    
    % effectuer la correction
    P_Y = zeros( length( Y_known ) , length( Y_known ) ); % covariance de Y_known
    for i = 1 : 2 : length( Y_known )
        P_Y( i : i + 1, i : i + 1 ) = coef * norm( Y_known( i : i + 1, 1 ) ) * eye( 2 );
    end
    if ~isempty( Y_known )
    K = Ps * H' / ( H * Ps * H' + P_Y ); % gain de Kalman
    X = Xs + K * ( Y_known - Ys );
    P = Ps - K * H * Ps;
    else
        X = Xs;
        P = Ps;
    end
    
    % rajouter les nouveaux amers
    for i = 1 : 2 : length( Y_new ) % mise à jour de la covariance de X
        P( end + 1 : end + 2, end + 1 : end + 2 ) = coef * norm( Y_new( i : i + 1, 1 ) ) * eye( 2 );
        X( end + 1 : end + 2, 1 ) = Y_new( i : i + 1, 1 ) + X( 1 : 2, 1 );
    end % les éléments de Y sont en coordonnées relatives et ceux de X en coordonnées absolues
    B = zeros( length( X ), 2 );
    B( 1 : 2, : ) = eye( 2 );
    
    % afficher la carte et enregistrer
    plot( Xs( 1 ), Xs( 2 ), 'ks' ); % chemin prédit
    viscircles( [Xs( 1 ) Xs( 2 )], Ps( 1, 1 ), 'Color', 'b', 'LineWidth', 0.3, 'LineStyle', ':' );
    Pred_x( end + 1 ) = Xs( 1 );
    Pred_y( end + 1 ) = Xs( 2 );
    plot( Pred_x, Pred_y, 'b:' );
    plot( X( 1 ), X( 2 ), 'ks' ); % chemin corrigé
    viscircles( [X( 1 ) X( 2 )], P( 1, 1 ), 'Color', 'k', 'LineWidth', 0.5 );
    Corr_x( end + 1 ) = X( 1 );
    Corr_y( end + 1 ) = X( 2 );
    plot( Corr_x, Corr_y, 'k' );
    for i = 3 : 2 : length( X ) % amers
        plot( X( i ), X( i + 1 ), 'rx' );
        viscircles( [X( i ) X( i + 1 )], P( i, i ), 'Color', 'r', 'LineWidth', 0.5 );
    end
    writeVideo( video, getframe( gcf ) );
    
end
fclose( FileID );
close( video );