:- use_module(library(clpfd)).


/* EXERCICE 2 */

equation(Lettres) :-
	
	/* Variables et Domaines */ 

	Lettres = [C,P,I,S,F,U,N,T,R,E],

	Lettres ins 0..9,

	/* Contraintes */ 

	all_distinct(Lettres),
	C*10 + P + 10*I + S + 100*F + 10*U + N #= 1000*T + 100*R + 10*U + E,
	C #\= 0,
	I #\= 0,
	F #\= 0,
	T #\= 0,

	/* Recherche */ 
	label(Lettres).

