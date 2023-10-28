/* Ce fichier est encodé en UTF-8 et suit la syntaxe du langage Prolog		*/
/* Merci de NE PAS MODIFIER LE SYSTEME D'ENCODAGE		*/

/* Nom du binome :    FANTINO - HUBERT		*/

/*****************************************************************************
*              Modélisation du domaine du problème des cruches
******************************************************************************/


/*****************************************************************************
* Question 0 :  
*
* Proposer une structure permettant de représenter un état pour le problème
* des cruches (nb il n'y a pas de relation à définir - décrire juste la
* structure que vous comptez utiliser, en précisant le sens de chaque argument)
*
* Réponse : 
*			On propose une structure de liste de forme cruches(C1,C2)
*
* où 
			C1 représente le remplissage de la cruche 1
			C2 représente le remplissage de la cruche 2
******************************************************************************/



/*****************************************************************************
* Question 1 : Définir un prédicat constructeur/accesseur, permettant de faire
* abstraction de la structure que vous avez choisie (et d'automatiser les test)



* cons_etat_cruche(?P, ?G, ?Etat)  

	qui est vrai si et seulement si Etat correspond au terme
	modélisant un état du domaine des cruches dans lequel 
	- le contenu de la petite cruche est P
	- le contenu de la grande cruche est G
******************************************************************************/


cons_etat_cruche(P,G,cruches(P,G)).


/*****************************************************************************
* Question 2 : Ecrire le code du prédicat :

* etat_cruche(?Terme)  qui est vrai si et seulement si Terme est un terme prolog
*                      qui représente bien un état pour le problème des cruches.
******************************************************************************/


volume_max(cruches(5,7)).


etat_cruche(cruches(P,G)):-
	volume_max(cruches(Volume1,Volume2)),
	P =< Volume1,
	P >= 0, 
	G =< Volume2,
	G >= 0.


/*****************************************************************************
* Question 3 : Définir un prédicat :

* operateur(?Nom,?Etat,?NEtat)
					qui est vrai si et seulement si Nom est le nom d'un opérateur 
*					applicable pour le problème des cruches, permettant de  
					passer d'un état Etat à un successeur état NEtat.
******************************************************************************/


operateur(remplir_G,cruches(P,G),cruches(P,Volume2)):-
	volume_max(cruches(_,Volume2)),
	G < Volume2.
operateur(remplir_P,cruches(P,G),cruches(Volume1,G)):-
	volume_max(cruches(Volume1,_)),
	P < Volume1.
operateur(vider_G,cruches(P,G),cruches(P,0)):-
	G > 0.
operateur(vider_P,cruches(P,G),cruches(0,G)):-
	P > 0.
operateur(transvaser_G,cruches(P,G),cruches(PT,GT)):-
	volume_max(cruches(_,Volume2)),
	P > 0,
	G < Volume2,
	PT is max(0,P+G-Volume2),
	GT is min(P+G,Volume2).
operateur(transvaser_P,cruches(P,G),cruches(PT,GT)):-
	volume_max(cruches(Volume1,_)),
	P < Volume1,
	G > 0,
	PT is min(P+G,Volume1),
	GT is max(0,P+G-Volume1).


/*****************************************************************************
* Question 4 : Définir le prédicat : 
* but(?Etat)   qui est vrai si et seulement si Etat est un état but pour 
*              le problème des cruches.
******************************************************************************/


volume_but(4).


but(cruches(P,_)):-
	volume_but(P).
but(cruches(_,G)):-
	volume_but(G).
