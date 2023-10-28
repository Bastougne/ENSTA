/* Ce fichier est encodé en UTF-8 et suit la syntaxe du langage Prolog		*/
/* Merci de NE PAS MODIFIER LE SYSTEME D'ENCODAGE		*/


/* Nom du binome :    FANTINO - HUBERT		*/

/*****************************************************************************
* On suppose que l'on dispose d'un domaine de problème, caractérisé par 
*
*  - une relation operateur/3
*  - une relation but/1
*
* On souhaite coder un algorithme de recherche de chemin solution de faisant 
* aucune autre hypothèse que celle de la modélisation du domaine du problème
* a l'aide des relations précédentes.
*
* Définir les relations suivantes : 
******************************************************************************/


/*****************************************************************************
* rprof(+Etat,-Solution)	 qui est vrai si et seulement si Solution est une suite
*					         d'états caractérisant un chemin solution depuis Etat
*						     vers un état du But.
******************************************************************************/


rprof(E,[]) :-
	but(E).
rprof(E,[ES|S]) :-
	operateur(_,E,ES),
	rprof(ES,S).


/*****************************************************************************
* rprof_ss_cycle(+Etat,-Solution)	  qui est vrai si et seulement si Solution est 
*			une suite d'états sans cycle, caractérisant un chemin solution depuis
*			Etat vers un état du But.
******************************************************************************/


test_app(E,[F|_]) :-
	E == F,
	!.
test_app(E,[_|L]) :-
	test_app(E,L).


rprof_ss_cycle(E,S) :-
	rprof_ss_cycle_aux(E,S,[]).


rprof_ss_cycle_aux(E,P,P) :-
	but(E).
rprof_ss_cycle_aux(E,S,P) :-
	operateur(_,E,ES),
	not(test_app(ES,P)),
	rprof_ss_cycle_aux(ES,S,[ES|P]).


/*****************************************************************************
* Une nouvelle version de ce prédicat permettant limiter
* la profondeur de recherche.
*  
* rprof_bornee(+Etat,-Solution,+ProfMax)
*     qui est vrai si et seulement si Solution est une suite d'au plus ProfMax
*	  états caractérisant un chemin solution depuis Etat vers un état du But.
******************************************************************************/


rprof_bornee(E,S,Pmax) :-
	rprof_bornee_aux(E,S,[],Pmax).


rprof_bornee_aux(E,P,P,_) :-
	but(E).
rprof_bornee_aux(E,S,P,Pmax) :-
	Pmax >= 0,
	operateur(_,E,ES),
	not(test_app(ES,P)),
	Pmax1 is Pmax - 1,
	rprof_bornee_aux(ES,S,[ES|P],Pmax1).


/*****************************************************************************
* rprof_incr(+Etat,-Solution,+ProfMax)
*     qui est vrai si et seulement si Solution est une suite d'au plus ProfMax
*	  états caractérisant recherchée suivant une stratégie de recherche itérative
*     à profondeur incrémentale.
******************************************************************************/


rprof_incr(E,S,ProfMax) :-
	rprof_incr_aux(E,S,0,ProfMax).


rprof_incr_aux(E,S,Pmax,Pmax) :-
	rprof_bornee(E,S,Pmax).
rprof_incr_aux(E,S,Pmax,ProfMax) :-
	Pmax1 is Pmax + 1,
	rprof_incr_aux(E,S,Pmax1,ProfMax).