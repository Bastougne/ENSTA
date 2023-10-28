:- use_module(library(clpfd)).


/* EXERCICE 1 */

cinqPersonnes(Vars) :-

	/* Variables et Domaines */

	Nationalites = [Anglais, Espagnol, Japonais, Italien, Norvegien],
	Couleurs = [Rouge, Vert, Blanc, Jaune, Bleu],
	Boissons = [The, Cafe, Lait, JusFruits, Eau],
	Animaux = [Chien, Escargots, Renard, Cheval, Zebre],
	Professions = [Peintre, Sculpteur, Diplomate, Violoniste, Medecin],

	flatten([Nationalites, Couleurs, Boissons, Animaux, Professions], Vars),
	Vars ins 1..5, 


	/* Contraintes */

	all_distinct(Nationalites),
	all_distinct(Professions),
	all_distinct(Boissons),
	all_distinct(Animaux),
	all_distinct(Couleurs),

	/*1. L’anglais habite la maison rouge*/
	Anglais #= Rouge,
	/*2. L’espagnol possède un chien.*/
	Espagnol #= Chien,
	/*3. Le japonais est peintre.*/
	Japonais #= Peintre,
	/*4. L’italien boit du thé.*/
	Italien #= The,
	/*5. Le norvégien habite la première maison à gauche.*/
	Norvegien #= 1,
	/*6. Le propriétaire de la maison verte boit du café.*/
	Vert = Cafe,
	/*7. La maison verte est à droite de la blanche.*/
	Vert #= Blanc + 1,
	/*8. Le sculpteur élève des escargots.*/
	Sculpteur #= Escargots,
	/*9. Le diplomate habite la maison jaune.*/
	Diplomate #= Jaune,
	/*10. On boit du lait dans la maison du milieu.*/
	Lait = 3,
	/*11. Le norvégien habite à coté de la maison bleue.*/
	Norvegien = Bleu + 1,
	/*12. Le violoniste boit des jus de fruits.*/
	Violoniste #= JusFruits,
	/*13. Le renard est dans la maison voisine du médecin.*/
	abs(Renard - Medecin) #= 1, 
	/*14. Le cheval est à coté de celle du diplomate.*/
	abs(Cheval - Diplomate) #= Diplomate,

	/* Recherche */
	label(Vars).
