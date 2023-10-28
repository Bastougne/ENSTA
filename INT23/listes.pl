dans_liste(E,[E|_]).		/* E = element, L = liste, element dans la liste */
dans_liste(E,[_|L]) :-
	dans_liste(E,L).


taille_paire([]).		/* L = liste de taille paire */
taille_paire([_,_|L]) :-
	taille_paire(L).


taille_impaire([_]).		/* L = liste de taille impaire */
taille_impaire([_,_|L]) :-
	taille_impaire(L).


concatene([],L,L).		/* LA = liste 1, LB = liste 2, LC = liste concatenee */
concatene([XA|LA],LB ,[XA|LC]) :-
	concatene(LA,LB,LC).


renverse([],[]).		/* L = liste, LR = liste en sens inverse */
renverse([E|L],LR) :-
	concatene(LRtempo,[E],LR),
	renverse(L,LRtempo).


efface(E,[E|L],L).		/* E = element a retirer, L = liste, NL = liste apres suppression */
efface(E,[F|L],[F|NL]) :-	/* de la premiere occurrence de E */
	F\=E,
	efface(E,L,NL).


efface_tout(_,[],[]).		/* E = element a retirer, L = liste, NL = liste apres suppression */
efface_tout(E,[E|L],NL) :-	/* de toutes les occurrences de E */
	efface_tout(E,L,NL).
efface_tout(E,[F|L],[F|NL]) :-
	F\=E,
	efface_tout(E,L,NL).


permute([],[]).			/* L = liste, PL = liste permutee */
permute([E|L],PL) :-
	efface(E,PL,PLtempo),
	permute(L,PLtempo).


taille(L,N):-			/* L = liste, N = taille de la liste */
	taille_aux(L,N,0).

taille_aux([],N,N).
taille_aux([_|L],N,A):-
	A1 is A + 1,
	taille_aux(L,N,A1).


somme(L,S):-			/* L = liste, S = somme des éléments de la liste */
	somme_aux(L,S,0).

somme_aux([],S,S).
somme_aux([E|L],S,A):-
	A1 is A + E,
	somme_aux(L,S,A1).