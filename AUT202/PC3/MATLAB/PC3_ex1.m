clear all
close all


x0 = randn()    % condition initiale en position (al�atoire)
dx0 = randn()   % condition initiale en vitesse (al�atoire)

A = [ 0 1;
     -1 0]
B = [0;
     1];

Q1 = 1          % co�t de la commande "moyen"
Q2 = 10         % co�t de la commande "�l�v�"
Q3 = 0.1        % co�t de la commande "faible"
R = [1 0;
     0 1]

K1 = lqr(A, B, R, Q1)   % gain associ� � Q1
K2 = lqr(A, B, R, Q2)   % gain associ� � Q2
K3 = lqr(A, B, R, Q3)   % gain associ� � Q3