permute([],[]).
permute([E|L],LP):-
	efface(E,LP,LPN),
	permute(L,LPN).


/* permet d'accéder au ième élément d'une liste */
element_i(L,I,E):-
	element


/* LL est la liste contenant les listes correspondant aux lignes */
colonne_i(LL,I,C):-





/* Résolveur L liste des lignes, LR liste des lignes après résolution */ 
resolve_sudoku(L,LR):-
	