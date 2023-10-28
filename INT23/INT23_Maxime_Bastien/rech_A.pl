/* Ce fichier est encodé en UTF-8 et suit la syntaxe du langage Prolog      */
/* Merci de NE PAS MODIFIER LE SYSTEME D'ENCODAGE     */


/*****************************************************************************
* rech_A(+Etat,-Solution,H,NNA,NND)	  qui est vrai si et seulement si Solution est 
*			une suite (sans cycle) d'états, caractérisant un chemin solution depuis
*			Etat vers un état du But, renvoyé par l'algorithme A* en utilisant
* 			la fonction heuristique H. NNA et NND représentent respectivement le `
* 			nombre total de noeuds apparus (i.e. la taille du graphe de recherche)
* 			et le nombre de noeuds développés.
******************************************************************************/

:- dynamic g/2.
:- dynamic f/2.


rech_A(Etat,Solution,H,NNA,NND) :-
	retractall(g(_,_)),
	retractall(f(_,_)),
	assertz(g(Etat,0)),
	X =.. [H,Etat,Val],
	X,
	assertz(f(Etat,Val)),
	rech_A_aux(Solution,H,NNA,NND,[],[nd(Etat,nil)],1,0).


rech_A_aux(Solution,_,NNA,NND,_,Frontiere,NNA,NND) :-
	member(nd(Etat,Pere),Frontiere),
	but(Etat),
	!,
	construire_solution(nd(Etat,Pere),Solution).

rech_A_aux(Solution,H,NNA,NND,DejaDev,Frontiere,NNAAcc,NNDAcc) :-
	choixMini(Frontiere,nd(Etat,Pere)),
	delete(Frontiere,nd(Etat,Pere),Frontiere1),
	findall(Suivant,operateur(_,Etat,Suivant),Successeurs),
	miseAJour(Successeurs,nd(Etat,Pere),H,[Etat|DejaDev],Frontiere1,Frontiere2,N,0),
	NNAAcc1 is NNAAcc + 1,
	NNDAcc1 is NNDAcc + N,
	rech_A_aux(Solution,H,NNA,NND,[Etat|DejaDev],Frontiere2,NNAAcc1,NNDAcc1).

choixMini([Etat],Etat).

choixMini([Etat1,Etat2|Reste],Mini) :-
	not(f(Etat1,_)),
	!,
	choixMini([Etat2|Reste],Mini).

choixMini([Etat1,Etat2|Reste],Mini) :-
	not(f(Etat2,_)),
	!,
	choixMini([Etat1|Reste],Mini).

choixMini([Etat1,Etat2|Reste],Mini) :-
	f(Etat1,Val1),
	f(Etat2,Val2),
	Val1 < Val2,
	!,
	choixMini([Etat1|Reste],Mini).

choixMini([_,Etat2|Reste],Mini) :-
	choixMini([Etat2|Reste],Mini).


miseAJour([],_,_,_,Frontiere,Frontiere,N,N).

miseAJour([Suivant|Successeurs],nd(Cruches,Parents),H,DejaDev,Frontiere,Frontiere1,N,NAcc) :-
	not(member(Suivant,DejaDev)),
	not(member(Suivant,Frontiere)),
	!,
	g(Cruches,GEtat),
	GSuivant is GEtat + 1,
	retractall(g(Suivant,_)),
	assertz(g(Suivant,GSuivant)),
	X =.. [H,Suivant,HSuivant],
	X,
	FSuivant is GSuivant + HSuivant,
	retractall(f(Suivant,_)),
	assertz(f(Suivant,FSuivant)),
	NAcc1 is NAcc + 1,
	miseAJour(Successeurs,nd(Cruches,Parents),H,DejaDev,[nd(Suivant,nd(Cruches,Parents))|Frontiere],Frontiere1,N,NAcc1).

miseAJour([nd(Cruches,Parents)|Successeurs],nd(Cruches,Parents),H,DejaDev,Frontiere,Frontiere1,N,NAcc) :-
	g(Cruches,GEtat),
	g(Suivant,GSuivant),
	GSuivant > GEtat + 1,
	!,
	delete(DejaDev,nd(Cruches,Parents),DejaDev2),
	miseAJour(Successeurs,nd(Cruches,Parents),H,DejaDev2,[nd(Suivant,nd(Cruches,Parents))|Frontiere],Frontiere1,N,NAcc).

miseAJour([_|Successeurs],Etat,H,DejaDev,Frontiere,Frontiere1,N,NAcc) :-
	miseAJour(Successeurs,Etat,H,DejaDev,Frontiere,Frontiere1,N,NAcc).


construire_solution(nd(Etat,nil),[Etat]).

construire_solution(nd(Etat,Pere),[Etat|Solution]):-
	construire_solution(Pere,Solution).
