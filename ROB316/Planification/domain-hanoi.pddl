(define (domain HANOI)
(:requirements :strips)
(:predicates
	(disque ?x)
	(pic ?x)
	(sur-disque ?x ?y)
	(sur-pic ?x)
	(rien-sur ?x)
	(main-vide)
	(dans-main ?x)
	(plus-grand ?x ?y)
)

(:action transitivite-tailles ;;; simplifie la description du monde
	:parameters (?gd ?md ?pd)
	:precondition
		(and (disque ?gd) (disque ?md) (disque ?pd)
		(plus-grand ?gd ?md) (plus-grand ?md ?gd)) ;;; si gd est plus grand que md, qui est plus grand que pd
	:effect
		(plus-grand ?gd ?pd) ;;; alors gd est plus grand que pd
)

(:action prendre-sur-pic
	:parameters (?d ?p)
	:precondition
		(and (disque ?d) (pic ?p)
		(sur-pic ?d ?p) (rien-sur ?d)
		(main-vide))
	:effect
		(and (not(sur-pic ?d ?p)) (rien-sur ?p)
		(not(main-vide)) (dans-main ?d))
)

(:action prendre-sur-disque
	:parameters (?d ?ssd)
	:precondition
		(and (disque ?d) (disque ?ssd)
		(sur-disque ?d ?ssd) (rien-sur ?d)
		(main-vide))
	:effect
		(and (not(sur-disque ?d ?ssd)) (rien-sur ?ssd)
		(not(main-vide)) (dans-main ?d))
)

(:action poser-sur-pic
	:parameters (?d ?p)
	:precondition
		(and (disque ?d) (pic ?p)
		(rien-sur ?p) (dans-main ?d))
	:effect
		(and (not(rien-sur ?p)) (sur-pic ?d ?p)
		(not(dans-main ?d)) (main-vide))
)

(:action poser-sur-disque
	:parameters (?d ?ssd)
	:precondition
		(and (disque ?d) (disque ?ssd)
		(rien-sur ?ssd) (dans-main ?d)
		(plus-grand ?ssd ?d))
	:effect
		(and (not(rien-sur ?ssd)) (sur-disque ?d ?ssd)
		(not(dans-main ?d)) (main-vide))
)
)