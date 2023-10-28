long1([],0).			/* L = liste, N = long3 de la liste */
long1([_|L],N) :-
	long1(L,NN),
	N = NN + 1.


long3(L,N) :-			/* L = liste, N = long3 de la liste */
	long3_aux(L,N,0).

long3_aux([],N,N).
long3_aux([_|L],N,A) :-
	A1 is A+1,
	long3_aux(L,N,A1).


somme(L,S) :-			/* L = liste, S = somme des elements de la liste */
	somme_aux(L,S,0).

somme_aux([],S,S).
somme_aux([E|L],S,A) :-
	A1 is A+E,
	somme_aux(L,S,A1).

moyenne([],0).			/* L = liste, M = moyenne */
moyenne(L,M) :-
	somme(L,S),
	long3(L,N),
	M is S/N.


somme_carre(L,S) :-		/* L = liste, S = somme des carres des elements de la liste */
	somme_carre_aux(L,S,0).

somme_carre_aux([],S,S).
somme_carre_aux([E|L],S,A) :-
	A1 is A+E*E,
	somme_carre_aux(L,S,A1).


variance([],0).			/* L = liste, V = variance de la liste */
variance(L,V) :-
	moyenne(L,M),
	somme_carre(L,S),
	long3(L,N),
	V is S/N-M*M.


ecart_type(L,ET) :-		/* L = liste, ET = ecart-type */
	variance(L,V),
	ET is sqrt(V).


efface(E,[E|L],L).		/* E = element a retirer, L = liste, NL = liste apres suppression */
efface(E,[F|L],[F|NL]) :-	/* de la premiere occurrence de E */
	F\=E,
	efface(E,L,NL).


permute([],[]).			/* L = liste, PL = liste permutee */
permute([E|L],PL) :-
	efface(E,PL,PLtempo),
	permute(L,PLtempo).

ordonnee([]).			/* L = liste ordonnee */
ordonnee([_]).
ordonnee([E,F|L]):-
	E<F;E=F,
	ordonnee([F|L]).

tri(L,LT) :-			/* L : liste, LT = liste triee */
	permute(L,LT),
	ordonnee(LT).