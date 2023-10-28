# Ce fichier doit se nommer de pr�f�rence Makefile ou bien makefile
# car la commande `make', sans argument, cherche une description de
# projet dans un fichier nomm� `makefile' ou `Makefile' (dans cet
# ordre).

# La commande `make' cherchera � mettre � jour la premi�re cible du
# makefile (ici, compte).

compte:  cptlex.cmo compte.cmo
	ocamlc -o compte cptlex.cmo compte.cmo

# Pour compiler compte.ml, on doit disposer de l'interface compil�e cptlex.cmi
# qui est produite en m�me temps que cptlex.cmo. C'est en effet cptlex.cmi qui
# est consult�e par le compilateur OCaml pour savoir quel est le type de
# Cptlex.count, utilis�e par compte.ml
# le fichier compte.cmo d�pend donc de cptlex.cmo
compte.cmo: compte.ml cptlex.cmo
	ocamlc -c compte.ml

cptlex.cmo: cptlex.ml
	ocamlc -c cptlex.ml

cptlex.ml: cptlex.mll
	ocamllex cptlex.mll

# Il peut exister de fausses cibles (comme `clean' ci-dessous).

clean:
	/bin/rm -f *.cmo *.cmi cptlex.ml compte

