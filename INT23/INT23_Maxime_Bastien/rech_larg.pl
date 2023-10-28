/* Ce fichier est encodé en UTF-8 et suit la syntaxe du langage Prolog      */
/* Merci de NE PAS MODIFIER LE SYSTEME D'ENCODAGE     */

/* Nom du binome :    FANTINO - HUBERT										 */

/*****************************************************************************
*					          PARTIE 4
*
* L'algorithme de recherche en profondeur s'implémente tres facilement en Prolog
* car la stratégie de preuve mise en oeuvre par le démonstrateur de Prolog
* suit elle même une stratégie en profondeur.
* 
* Le codage de l'algorithme de recherche en largeur est un peu moins direct
* car on a besoin de pouvoir connaitre tous les Successeursesseurs d'un état.
*
* Pour cela il existe un prédicat prédéfini en prolog, qui permet de trouver
* toutes les solutions d'un but. Ce prédicat s'appelle findall/3.
*
******************************************************************************/


/*****************************************************************************
1) lisez la documentation de ce prédicat en tapant help(findall/3)
     et testez le sur des exemples simples pour bien comprendre comment
     fonctionne ce prédicat.
******************************************************************************/


/* findall(+Template, :Goal, -Bag)                                                            [ISO]
      Create a list of the instantiations Template gets Succesessively on backtracking over Goal and
      unify the result with Bag. Successeurseeds with an empty list if Goal has no solutions.  */

meteo(lundi,pluie).
meteo(mardi,pluie).
meteo(mercredi,soleil).

/* ?- findall(Jour,meteo(Jour,pluie),Bag).
   Bag = [lundi, mardi]. */


/*****************************************************************************
* 2) Pour connaître les tous les succeseurs d'un état E il suffira alors 
* d'utiliser :
*      	...
*       findall(NE, operateur(OP,E,NE), Successeurs)
*       ....
*
* > vérifiez cela manuellement sur quelques états des cruches et/ou du taquin
* > nb : à la place de NE, vous pouvez aussi mettre n'importe quel terme qui contient NE.
******************************************************************************/


/* ?- findall(NE,operateur(OP,cruches(0,0),NE),Successeurs).
   Successeurs = [cruches(0, 7), cruches(5, 0)]. */


/* ?- findall(NE,operateur(OP,cruches(0,2),NE),Successeurs).
   Successeurs = [cruches(0, 7), cruches(5, 2), cruches(0, 0), cruches(2, 0)]. */


/* ?- findall(NE,operateur(OP,cruches(1,3),NE),Successeurs).
   Successeurs = [cruches(1, 7), cruches(5, 3), cruches(1, 0), cruches(0, 3), cruches(0, 4), cruches(4, 0)]. */


/*****************************************************************************
* 3) Le codage de l'algorithme de recherche en profondeur nécessite alors
* de construire le graphe de recherche et sa frontière.
* une façon simple de représenter la structure de ce graphe est de 
* représenter chaque noeud par une structure de la forme : 
*
*      nd(E, Pere) 
* 
* où - E est l'état associé au noeud
*    - Pere est le noeud parent de ce noeud (ou nil si le noeud correspond à l'état initial)
* 
* On peut alors représenter la frontière simplement par une liste de noeuds.
* mais pour garantir que l'exploration s'effectue bien en largeur il faudra bien
* veiller à développer à chaque étape, le noeud le plus ancien parmi ceux de la frontière
* (attention à la façon dont vous rajoutez des noeuds à la frontière).
******************************************************************************/


/*****************************************************************************
* Definir le prédicat :
* rech_larg(+E,-Sol,-NNA,-NND) 
*		qui construit un chemin solution Sol depuis l'état E, en construisant le graphe
*        de recherche suivant une stratégie en largeur d'abord.
*		-NNA,-NND sont des entiers correspondants respectivement au nombre de noeuds
*		 apparus et développés 
*
* nb : Vous aurez besoin de définir 
*		- une procédure auxiliaire, qui explicite la frontière du graphe et les états déjà
*		- developpés et effectue la recherche
*		- une procédure auxiliaire qui reconstruit le chemin solution lorsqu'un état but a été atteint.
******************************************************************************/


rech_larg(Etat,Solution,NNA,NND) :-
	rech_larg_aux(Solution,NNA,NND,[],[nd(Etat,nil)],1,0).


rech_larg_aux(Solution,NNA,NND,_,[nd(Etat,Pere)|_],NNA,NND) :-
	but(Etat),
	!,
	construire_solution(nd(Etat,Pere),Solution).

rech_larg_aux(Solution,NNA,NND,DejaDev,[nd(Etat,Pere)|Frontiere],NNAAcc,NNDAcc) :-
	findall(Suivant,operateur(_,Etat,Suivant),Successeurs),
	miseAJour(Successeurs,nd(Etat,Pere),[Etat|DejaDev],Frontiere,Frontiere1,N,0),
	NNAAcc1 is NNAAcc + 1,
	NNDAcc1 is NNDAcc + N,
	rech_larg_aux(Solution,NNA,NND,[Etat|DejaDev],Frontiere1,NNAAcc1,NNDAcc1).


miseAJour([],_,_,Frontiere,Frontiere,N,N).

miseAJour([Suivant|Successeurs],Etat,DejaDev,Frontiere,Frontiere1,N,NAcc) :-
	not(member(Suivant,DejaDev)),
	not(member(Suivant,Frontiere)),
	!,
	append(Frontiere,[nd(Suivant,Etat)],Frontiere2),
	NAcc1 is NAcc + 1,
	miseAJour(Successeurs,Etat,DejaDev,Frontiere2,Frontiere1,N,NAcc1).

miseAJour([_|Successeurs],Etat,DejaDev,Frontiere,Frontiere1,N,NAcc) :-
	miseAJour(Successeurs,Etat,DejaDev,Frontiere,Frontiere1,N,NAcc).


construire_solution(nd(Etat,nil),[Etat]).

construire_solution(nd(Etat,Pere),[Etat|Solution]):-
	construire_solution(Pere,Solution).
