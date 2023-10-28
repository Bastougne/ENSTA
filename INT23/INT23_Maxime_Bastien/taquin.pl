/* Ce fichier est encodé en UTF-8 et suit la syntaxe du langage Prolog      */
/* Merci de NE PAS MODIFIER LE SYSTEME D'ENCODAGE     */

/* Nom du binome :    FANTINO - HUBERT     										 */
/*           (TODO : remplacez Nom1 et Nom2 par vos noms dans l'ordre alphabétique) */

/*****************************************************************************
 			    Introduction à l'Intelligence Artificielle					 
					ENSTA 1ère année - Cours INT23
*****************************************************************************/

/*****************************************************************************
* On considère le domaine de problème correspondant au jeu du taquin sur une
* grille de taille 4x4 et on décide de représenter un état par une structure 
* de la forme :
*  
*     et( A, B, C, D
*		  E, F, G, H
*		  I, J, K, L,
*		  M, N, O, P,
*		  CV
*		 )
*
* tel que : 
* - A,...,P représentent respectivement les contenus des 
*   différentes cases de la grille du taquin, lorsqu'elle est 
*	parcourue de haut en bas et de gauche à droite.
*   ils correspondent à des entiers tous différentes allant de 0 à 15 
*   (où 0 représente la case vide) 
*
* - CV représente le numéro de l'argument correspondant à la case vide 
*
* Exemple :  la grille suivante :
*
*				1   2   3   4  
*				5   6   7   8  
*				9  10  11  12  
*			   13  14  15   0  
*
*     sera représentée par le terme 
*		et(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,16)
*		car la position de la case vide correspond au 16e argument de la structure.
*
*  NB1  : l'information représentée par CV est redondante, mais elle évite d'avoir 
*         à parcourir la structure pour retrouver la position de la case vide
*
*  NB2  : cette représentation n'est pas optimale en terme d'espace
*		 On pourait par exemple représenter
*        la grille par un simple entier sur 64bits (4*16)	
* 		 mais elle est déjà plus économique qu'une simple liste de 16 entiers.		
*******************************************************************************/

/*****************************************************************************
 cons_etat_taquin(?Liste, ?EtatTaquin) est vrai 
				construit un  ?EtatTaquin à partir d'une grille 
				représentée par une simple liste dont les cases sont parcourues
				de gauche à droite  et de haut en bas (et inversement)
				
				mode d'appel (+,?) ou (?,+) 
				Ne vérifie pas que les cases sont bien remplies par des
				entiers entre 0 et 15
******************************************************************************/
cons_etat_taquin(Matrice, EtatTaquin) :-
		     Matrice = [A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P],
		     EtatTaquin =.. [et,A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,CV],
			 arg(CV,EtatTaquin,0).

/* tests
cons_etat_taquin([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0],E).
cons_etat_taquin([0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,1],E).
cons_etat_taquin([10,2,3,4,5,6,7,8,9,0,11,12,13,14,15,1],E).

cons_etat_taquin(M,et(0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 1)).

*/ 



/*****************************************************************************
* operateur(?Nom,?Etat,?NEtat) qui est vrai si et seulement si Nom est le nom
*							  d'un opérateur pour le problème du taquin
*							  applicable et permettant de faire passer d'un état
*							  Etat à un nouvel état NEtat.
******************************************************************************/


/* Les 4 seuls operateurs correspondent aux deplacements latteraux de la case vide */

operateur(gauche, Etat, NEtat) :-
	/* on recupere les listes associee aux etats */
	cons_etat_taquin(L, Etat),
	cons_etat_taquin(NL, NEtat),
	/* la position de la case vide est donnee par le dernier argument de l'etat */
	arg(17, Etat, CV),
	arg(17, NEtat, NCV),
	/* on verifie que la case vide ne soit pas sur l'extreme gauche */
	not(member(CV,[1,5,9,13])),	
	NCV is CV-1,
	/* la nouvelle position de la nouvelle liste doit correspondre a la casse vide */
	nth1(NCV, NL, 0),
	/* echange des deux valeurs */
	nth1(NCV, L, E),		 
	nth1(CV, NL, E).


/* On retrouve les memes explications donnees en commentaires pour les 3 operateurs suivants */

operateur(droite, Etat, NEtat) :-
	cons_etat_taquin(L, Etat),
	cons_etat_taquin(NL, NEtat),
	arg(17, Etat, CV),	
	arg(17, NEtat, NCV),
	not(member(CV,[4,8,12,16])),
	NCV is CV+1,		
	nth1(NCV, NL, 0),	
	nth1(NCV, L, E),		
	nth1(CV, NL, E).


operateur(haut, Etat, NEtat) :-
	cons_etat_taquin(L, Etat),
	cons_etat_taquin(NL, NEtat),
	arg(17, Etat, CV),
	arg(17, NEtat, NCV),
	not(member(CV,[1,2,3,4])),	
	NCV is CV-4,		
	nth1(NCV, NL, 0),
	nth1(NCV, L, E),
	nth1(CV, NL, E).


operateur(bas, Etat, NEtat) :-
	cons_etat_taquin(L, Etat),
	cons_etat_taquin(NL, NEtat),
	arg(17, Etat, CV),
	arg(17, NEtat, NCV),
	not(member(CV,[13,14,15,16])),
	NCV is CV+4,
	nth1(NCV, NL, 0),
	nth1(NCV, L, E),
	nth1(CV, NL, E).




	

/*****************************************************************************
* but(Etat)	  qui est vrai si et seulement si Etat est un état but pour 
*              le problème du taquin.
******************************************************************************/


but(Etat) :-
	cons_etat_taquin([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0], Etat).


/*****************************************************************************
*Avertissement : 
* pour tester vos algorithmes sur le problème du taquin, devez faire attention
* au fait que l'espace d'état est composé de deux parties non connectées.
* Si vous choisissez un état au hasard... il est possible qu'il ne figure pas 
* dans la même composante connexe que votre but... et dans ce cas le problème
* n'aura pas de solution.
*
* Suggestion : implémentez une relation qui à partir de l'état correspondant
* a votre but, applique au hasard des opérateurs un certain nombre de fois
* pour obtenir un état qui se trouve forcément dans la même composantte connexe 
* que votre but.
* 
******************************************************************************/

/* la troisieme liste correspond a la difference terme a terme de la premiere liste et la deuxieme */
difference_terme_a_terme([],[],[]).
difference_terme_a_terme([E1|L1],[E2|L2],[S|L3]) :-
	S is E1-E2,
	difference_terme_a_terme(L1,L2,L3).


/* codee lors du TP2, efface toutes les occurences de E dans L */
efface_tout(_,[],[]).
efface_tout(E,[E|L],NL):-
	efface_tout(E,L,NL).
efface_tout(E,[F|L],[F|NL]):-
	E\=F,
	efface_tout(E,L,NL).


/* donne le nombre d'elements a la mauvaise position dans la liste L en faisant la difference entre la liste L et la liste objectif puis en enlevant les 0 resultants (correspondant aux elements qui etaient bien places) puis en comptant le nombre d'elements qu'il reste */
mauvaise_position(L,N) :-
	difference_terme_a_terme(L,[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0],LD),
	efface_tout(0,LD,SL),
	length(SL,N).


/* avec toutes les fonctions precedentes, il suffit simplement de recuperer la liste correspondant a l'etat puis d'appeler mauvaise_position sur celle-ci */
h1(Etat,N) :-
	cons_etat_taquin(L,Etat),
	mauvaise_position(L,N).






/* renvoie la valeur absolue des elements d'une liste */
abs_list([],[]).
abs_list([E|L],[EA|AbsL]) :-
	abs(E,EA),
	abs_list(L,AbsL).


/* on procede comme pour h1 mais on somme les valeurs absolues a la fin, c'est a dire les distances de manhattan */
h2(Etat,N) :-
	cons_etat_taquin(L,Etat),
	difference_terme_a_terme(L,[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0],LD),
	abs_list(LD,LA),
	sumlist(LA,N).

h(_,1). /* Ceci est une heuristique de test */