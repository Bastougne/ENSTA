% regarder Picat

use_module(library(clpfd)).

zebre(Vars) :-
	Nationalites=[Anglais,Espagnol,Japonais,Italien,Norvegien],
	Professions=[Peintre,Sculpteur,Diplomate,Violoniste,Medecin],
	Boissons=[The,Cafe,Lait,Jus,Eau],
	Animaaux=[Chien,Escargot,Renard,Cheval,Zebre],
	Couleurs=[Rouge,Vert,Blanc,Jaune,Bleu],
	flatten([Nationalites,Professions,Boissons,Animaaux,Couleurs],Vars),
	Vars ins 1..5,
	all_distinct(Nationalites),
	all_distinct(Professions),
	all_distinct(Boissons),
	all_distinct(Animaaux),
	all_distinct(Couleurs),
	Anglais #= Rouge, % 1. L’anglais habite la maison rouge
	Espagnol #= Chien, % 2. L’espagnol possède un chien
	Japonais #= Peintre, % 3. Le japonais est peintre
	Italien #= The, % 4. L’italien boit du thé
	Norvegien #= 1, % 5. Le norvégien habite la première maison à gauche
	Vert #= Cafe, % 6. Le propriétaire de la maison verte boit du café.
	Vert #> Blanc, % 7. La maison verte est à droite de la blanche.
	Sculpteur #= Escargot, % 8. Le sculpteur élève des escargots.
	Diplomate #= Jaune, % 9. Le diplomate habite la maison jaune.
	Lait #= 3, % 10. On boit du lait dans la maison du milieu.
	Norvegien - Bleu #= -1 \/ 1, % 11. Le norvégien habite à coté de la maison bleue.
	Violoniste #= Jus, % 12. Le violoniste boit des jus de fruits.
	Renard - Medecin #= -1 \/ 1, % 13. Le renard est dans la maison voisine du médecin.
	Cheval - Diplomate #= -1 \/ 1, % 14. Le cheval est à coté de celle du diplomate.
	label(Vars),
	nl.

/* zebre([Anglais,Espagnol,Japonais,Italien,Norvegien,Peintre,Sculpteur,Diplomate,Violoniste,Medecin,The,Cafe,Lait,Jus,Eau,Chien,Escargot,Renard,Cheval,Zebre,Rouge,Vert,Blanc,Jaune,Bleu]). */


fun(Vars) :-
	Vars = [C,P,I,S,F,U,N,T,R,E],
	Vars ins 0..9,
	all_distinct(Vars),
	10*C+P + 10*I+S + 100*F+10*U+N #= 1000*T+100*R+10*U+E,
	label(Vars),
	C #\= 0,
	I #\= 0,
	F #\= 0,
	T #\= 0,
	label(Vars),
	nl.


carre(N,Vars) :-
	N2 is N^2,
	legnth(Vars,N2),
	Vars ins 1..N2,
	all_distinct(Vars),
	S is N*(N2-1)/2,
	lignes(N,Vars,S),
	colonnes(N,Vars,S),
	diagonales(N,Vars,S),
	label(Vars),
	nl.


somme(L,S) :-
	somme_aux(L,S,0).

somme_aux([],S,S).
somme_aux([E|L],S,A):-
	A1 is A+E,
	somme_aux(L,S,A1).


lignes(_,[],_).
lignes(N,Vars,S) :-
	append(Ligne,Reste,Vars),
	length(Ligne,N),
	somme(Ligne,S),
	lignes(N,Reste,S).


colonnes(_,0,[],_).
colonnes(N,N0,Vars,S) :-
	obtenir_colonne(N,N0,Vars,Colonne),
	somme(Colonne,S),
	N1 is N-1,
	colonnes(N,N1,Vars,Colonne).

obtenir_colonne(0,_,_,[]).
obtenir_colonne(N,N0,Vars,[E|Colonne]) :-
	nth0(