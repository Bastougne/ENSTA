/* Ne peut être appelé qu'avec des listes explicites */

long_pair([]).
long_pair([_,_|L]):-
	long_pair(L).

/* Ne peut être appelé qu'avec des listes explicites */

long_impair([_]).
long_impair([_,_|L]):-
	long_impair(L).
	

/* Utile pour définir renverse, ajoute E à la liste en position 1 pour donner la liste en position 3 */

ajout_fin([],E,[E]).
ajout_fin([F|L],E,[F|LA]):-
	ajout_fin(L,E,LA).

/* Peut être appelé en donnant explicitement les deux listes ou bien en demandant de construire la liste renversée */

renverse([],[]).
renverse([E|L],RL):-
	ajout_fin(T,E,RL),
	renverse(L,T).
	

/* Peut être appelé en donnant explicitement les deux listes ou bien en demandant de construire la liste avec E effacé */

efface(E,[E|L],L).
efface(E,[F|L],[F|NL]):-
	E\=F,
	efface(E,L,NL).



/* Peut être appelé en donnant explicitement les deux listes ou bien en demandant de construire la liste avec les E effacés */

efface_tout(_,[],[]).
efface_tout(E,[E|L],NL):-
	efface_tout(E,L,NL).
efface_tout(E,[F|L],[F|NL]):-
	E\=F,
	efface_tout(E,L,NL).
	
	


/* Ne peut être appelé qu'en fournissant explicitement une permutation de L */
permute([],[]).
permute([E|L],LP):-
	efface(E,LP,LPN),
	permute(L,LPN).