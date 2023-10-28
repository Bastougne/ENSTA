/* EXERCICE 2 */

/* on représente un ensemble par une liste non ordonnée et ne comportant pas deux fois le même élément */

efface(E,[E|L],L).	
efface(E,[F|L],[F|NL]):-	
	F\=E,
	efface(E,L,NL).


permut([],[]).			
permut([E|L],PL):-
	efface(E,PL,PLtempo),
	permut(L,PLtempo).




test_app(E,[F|_]):-
	E == F,
	!.
test_app(E,[F|L]):-
	E \= F,
	test_app(E,L).



adjoindre(E,Ensemble,Ensemble):-
	test_app(E,Ensemble),
	!.
adjoindre(E,Ensemble,[E|Ensemble]).



union([],B,B).
union([EA|A],B,AouB):-
	test_app(EA,B),
	!,
	union(A,B,AouB).
union([EA|A],B,[EA|AouB]):-
	union(A,B,AouB).


intersection([],_,[]).
intersection([EA|A],B,[EA|AetB]):-
	test_app(EA,B),
	!,
	intersection(A,B,AetB).
intersection([_|A],B,AetB):-
	intersection(A,B,AetB).


difference([],_,[]).
difference([EA|A],B,AmoinsB):-
	test_app(EA,B),
	!,
	difference(A,B,AmoinsB).
difference([EA|A],B,[EA|AmoinsB]):-
	difference(A,B,AmoinsB).



/* EXERCICE 3 */

applatir_aux([E|_],LA):-
	E is LA.


applatir([],[]).
applatir([E|L],[EA|LA]):-
	not(is_list(E)),
	applatir([L,LA]),
	!,
applatir([E|L],[EA|LA]):-







applique_subtitution([],_,[]).
applique_substitution([E|L],[S1|,[EN|LN]):-

	