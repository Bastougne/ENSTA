clear all
close all


x0 = randn()    % condition initiale en position (aléatoire)
dx0 = randn()   % condition initiale en vitesse (aléatoire)

A = [ 0 1;
     -1 0]
B = [0;
     1];

Q1 = 1          % coût de la commande "moyen"
Q2 = 10         % coût de la commande "élévé"
Q3 = 0.1        % coût de la commande "faible"
R = [1 0;
     0 1]

K1 = lqr(A, B, R, Q1)   % gain associé à Q1
K2 = lqr(A, B, R, Q2)   % gain associé à Q2
K3 = lqr(A, B, R, Q3)   % gain associé à Q3