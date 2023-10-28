/* EXERCICE 2*/

long1([],0).
long1([_|L],T):-
	long1(L,N),
	T is N+1.



long_aux([],N,N).
long_aux([_|Q],N,Acc):-
	Nacc is Acc + 1,
	long_aux(Q,N,Nacc).
	

long3(Q,N):-
	long_aux(Q,N,0).






/* EXERCICE 3 */

somme([],0).
somme([E|L],T):-
	somme(L,S),
	T is S+E.
	


moyenne([],0).	
moyenne(L,M):-
	long1(L,N),
	somme(L,S),
	M is S/N.
	


% retourne le carré des éléments d'une liste

carre_liste([],[]).
carre_liste([E1|L1],[E2|L2]):-
	E2 is E1*E1,
	carre_liste(L1,L2).

% soustrait une valeur aux éléments d'une liste

soustraction_liste([],[],_).
soustraction_liste([E1|L1],[E2|L2],S):-
	E2 is E1-S,
	soustraction_liste(L1,L2,S).

	
variance([],0).		 	
variance(L,V):-
	moyenne(L,M),
	soustraction_liste(L,LS,M),
	carre_liste(LS,CL),
	moyenne(CL,V).



ecart_type([],0).
ecart_type(L,E):-
	variance(L,V),
	E is sqrt(V).
	
	


/* EXERCICE 3 */

% on prend deux éléments pour les comparer, il faut donc repartir un cran avant pour éviter d'aller de deux en deux

ordonnee([]).
ordonnee([_]).
ordonnee([E1,E2|L]):-
	% disjonction pour '<='
	(E1<E2; E1=E2),
	ordonnee([E2|L]).



% on remet les fonctions du tp2 pour voir si une liste est une permutation d'une autre

efface(E,[E|L],L).	
efface(E,[F|L],[F|NL]):-	
	F\=E,
	efface(E,L,NL).


permut([],[]).			
permut([E|L],PL):-
	efface(E,PL,PLtempo),
	permut(L,PLtempo).


tri_rapide(L,LT):-
	permut(L,LT),
	ordonnee(LT).
	