/* on choisit de ressembler un ensemble par une liste sans répétition */

efface(E,[E|S],S).		/* E = element a retirer, S = ensemble, NS = ensemble apres suppression */
efface(E,[F|S],[F|NS]) :-
	efface(E,S,NS).


egaux([],[]).			/* E1 = representation 1 de l'ensemble, E2 = representation 2 */
egaux([E|S1],S2) :-
	efface(E,S2,Stempo),
	egaux(S1,Stempo).


test_app(E,[F|_]) :-		/* E = element dans l'ensemble, S = ensemble */
	E == F,
	!.
test_app(E,[_|S]) :-
	test_app(E,S).


adjoindre(E,S,S) :-		/* E = element, S = ensemnle, NS = ensemble avec l'element en plus */
	test_app(E,S),
	!.
adjoindre(E,S,[E|S]).


union([],S2,S2).		/* S1 = ensemble 1, S2 = ensemble 2, SU = S1 union S2 */
union([E|S1],S2,S3) :-
	test_app(E,S2),
	!,
	union(S1,S2,S3).
union([E|S1],S2,[E|S3]) :-
	union(S1,S2,S3).


intersection([],_,[]).		/* S1 = ensemble 1, S2 = ensemble 2, SI = S1 inter S2 */
intersection([E|S1],S2,[E|S3]) :-
	test_app(E,S2),
	!,
	intersection(S1,S2,S3).
intersection([_|S1],S2,S3) :-
	intersection(S1,S2,S3).


difference([],_,[]).		/* S1 = ensemble 1, S2 = ensemble 2, SD = S1 \ S2 */
difference([E|S1],S2,S3) :-
	test_app(E,S2),
	!,
	difference(S1,S2,S3).
difference([E|S1],S2,[E|S3]) :-
	difference(S1,S2,S3).


est_liste(A) :-			/* L = liste */
	var(A),
	!,
	fail.
est_liste([]).
est_liste([_|_]).


applatir(L,LA) :-		/* L = liste, LA = liste applatie */
	applatir_aux(L,LA,[]).


applatir_aux([],LA,LA).
applatir_aux([E|L],[E|LA],LAcc) :-
	not(est_liste(E)),
	!,
	applatir_aux(L,LA,LAcc).
applatir_aux([E|L],LA,LAcc) :-
	applatir_aux(E,LA,Ltempo),
	applatir_aux(L,Ltempo,LAcc).


test_app_unifiable(E,[F|_]) :-
	E = F,
	!.
test_app_unifiable(E,[_|S]) :-
	test_app_unifiable(E,S).


applique_substitution([],_,[]).	/* L = ancienne liste, S = substitution, LN = nouvelle liste */
applique_substitution([E|L],S,[F|LN]) :-
	test_app_unifiable(E/F,S),
	!,
	applique_substitution(L,S,LN).
applique_substitution([E|L],S,[E|LN]) :-
	applique_substitution(L,S,LN).
