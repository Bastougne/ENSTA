long_pair([]).
long_pair([_,_|L]):-
	long_pair(L).

long_impair([_]).
long_impair([_,_|L]):-
	long_impair(L).
	
	
concatene([],L,L).
concatene([XA|LA],LB,[XA|LC]):-
	concatene(LA,LB,LC).


renverse([],[]).
renverse([E|L],[RL|F]):-
	E==F,
	renverse(L,RL).
	

efface(E,[E|L],L).
efface(E,[F|L],[F|NL]):-
	E\=F,
	efface(E,L,NL).


permut([],[]).




	


