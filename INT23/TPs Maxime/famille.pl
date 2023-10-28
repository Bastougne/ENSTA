/* Ce fichier est encodé en UTF-8 et suit la syntaxe du langage Prolog      */

/*****************************************************************************
*              Modélisation d'un ensemble d'indvidus et de familles
******************************************************************************/


/*****************************************************************************
* individu(Cle,Prenom,Nom,DateDeNaissance,Activite) est une relation
  permettant de décrire dans une base de connaissance l'existence d'un individu
  et pour laquelle : 
   - Cle est une constante (supposé differente pour chaque individu)
   - Prenom et Nom sont des constantes
   - DateDeNaissance est une structure date(J,M,A) où
  		- J est un entier décrivant le numéro du jour de naissance dans le mois
  		- M est une constante décrivant le mois  de naissance
  		- A est un entier décrivant l'année de naissance
   - Activite est 
   		- soit la constante : inactif
   		- soit une structure : travaille(E, S) où
   			- E est une constante décrivant le nom de l'employeur
   			- S est un entier décrivant le salaire annuel de l'individu	
******************************************************************************/

individu(1, jean, dulac, date(7, mai, 1970),travaille(fr3, 35000)).
individu(2, anne, dulac, date(8, fev, 1972),travaille(edf, 45000)).
individu(3, rose, dulac, date(5, juin, 1996), inactif).
individu(4, pierre, dulac, date(15, aout, 1999), inactif).

individu(5, marc, dupont, date(7, mars, 1965),travaille(alcatel, 28000)).
individu(6, martine, dupont, date(22, mars, 1968),travaille(fnac, 22000)).
individu(7, alain, dupont, date(1, janv, 1990), inactif).
individu(8, michel, dupont, date(15, aout, 1993), inactif).
individu(9, helene, dupont, date(12, avril, 1995), inactif).

individu(10, lionel, bazar, date(7, sept, 1954),travaille(unisys, 35000)).
individu(11, martine,bazar, date(22, avril, 1956),travaille(ibm, 30000)).
individu(12, marc, bazar, date(24, fev, 1978),travaille(oracle, 48000)).

individu(13, celine, guezelec, date(24, octobre, 1983),inactif).

individu(14, cedric, poutou, date(13, juin, 1978),travaille(oracle, 23000)).
individu(15, valentin, lamour, date(14, fev, 1975),inactif).
individu(16, julien, cassis, date(29, fev, 1972),travaille(independant, 21000)).
individu(17, florence, groseille, date(30, novembre, 1970), travaille(independant, 9000)).
individu(18, lucie, seule, date(27, octobre, 1965),travaille(bull, 17000)).
individu(19, adrien, seule, date(3, mars, 1985),inactif).

/*****************************************************************************
* famille(Pere,Mere,ListeEnfants) est une relation
  permettant de décrire une famille telle que  : 
   - Pere est la clé identifiant le père
   - Mere est la clé identifiant le la mère
   - ListeEnfants est une liste de clés correspondant aux enfants  de cette famille.
******************************************************************************/

famille(1,2, [3,4]).
famille(5,6, [7,8,9]).
famille(10, 11 ,[12]).
famille(12, 13, []).
famille(14, 15, []).
famille(16, 17, []).


