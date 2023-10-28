(* Exercice 1 :*)

(* 1: *)
let id a = a;;

(* 2: *)
let cpt_voy chaine =
    let rec cpt_voy_rec chaine i =
        if i = String.length chaine then 0
        else match chaine.[i] with
        | ( 'a' | 'e' | 'i' | 'o' | 'u' | 'y' ) -> 1 + cpt_voy_rec chaine ( i + 1 )
        | _                                     -> cpt_voy_rec chaine ( i + 1 )
    in cpt_voy_rec chaine 0;;

(* 3: *)
let somme_inter ( a1, b1 ) ( a2, b2 ) =
    ( a1 + a2, b1 + b2 );;

(* 4: *)
let puiss_2 f x =
    f ( f x );;

(* 5: *)
let rec base8 x = if x < 8 then Int.to_string x else
    let y = x mod 8 in base8 ( ( x - y ) / 8 ) ^ Int.to_string y;;


(* Exercice 2: *)

(* 1: *)
type feu = ROUGE | ORANGE | VERT;;

let nom_feu nom = match nom with
    | ROUGE -> "rouge"
    | ORANGE -> "orange"
    | VERT -> "vert";;

(* 2: *)
type arbre = F | N of ( arbre * arbre );;

let rec prof_max arbre = match arbre with
    | F -> 1
    | N ( arbre1, arbre2 ) -> max ( prof_max arbre1 ) ( prof_max arbre2 );;


(* Exercice 3: *)

(* 1: *)
let rec dernier liste = match liste with
    | [] -> raise ( Failure "Liste trop courte !" )
    | e :: [] -> e
    | e :: reste -> dernier reste;;

(* 2: *)
let rec avant_dernier liste = match liste with
    | [] -> raise ( Failure "Liste trop courte !" )
    | e :: [] -> raise ( Failure "Liste trop courte !" )
    | e1 :: e2 :: [] -> e1
    | e1 :: e2 :: reste -> avant_dernier ( e2 :: reste );;

(* 3: *)
let rec nieme liste n =
    if n < 0 then raise ( Failure "Liste trop courte !" ) else
    if n = 0 then match liste with
        | [] -> raise ( Failure "Liste trop courte !" )
        | e :: _ -> e
    else match liste with
        | [] -> raise ( Failure "Liste trop courte !" )
        | e :: reste -> nieme reste ( n - 1 );;

(* 4: *)
let nieme_bis liste n = try Some (nieme liste n) with
    | Failure _ -> None;;

(* 5: *)
let rec copie liste = match liste with
    | [] -> []
    | e :: reste -> e :: copie reste;;

(* 6: *) (* merci le cours de Prolog de l'an dernier ;) *)
let renverse liste =
    let rec renverse liste acc = match liste with
        | [] -> acc
        | e :: reste -> renverse reste ( e :: acc )
    in renverse liste [];;

(* 7: *)
let rec sans_repetition liste =
    let rec supprimer x liste = match liste with
        | [] -> []
        | y :: reste -> if x = y then supprimer x reste else y :: supprimer x reste
    in match liste with
    | [] -> []
    | x :: reste -> x :: sans_repetition ( supprimer x reste );;

(* 8: *)
let trie_selon_la_longueur liste =
    (* passer à l'opposé pour trier par ordre décroissant *)
    let comparer_tailles l1 l2 = ( List.length l1 ) - ( List.length l2 )
    in List.sort comparer_tailles liste;;

(* 9: *)
let appl_1_sur_2 f liste =
    let rec appl_1_sur_2 f liste (appl : bool) = match liste with
    | [] -> []
    | x :: reste -> let reste_ = appl_1_sur_2 f reste ( not appl )
        in if appl then ( f x ) :: reste_ else reste_
    in appl_1_sur_2 f liste true;;

(* 10: *)
let tableau_de_liste tableau =
    let rec tableau_de_liste tableau i =
        if i = Array.length tableau then
            [] else tableau.(i) :: tableau_de_liste tableau ( i + 1 )
    in tableau_de_liste tableau 0;;

(* 11: *)
let rec separe liste = match liste with
    | [] -> [], []
    | x :: reste -> let pair, impair = separe reste
        in if x mod 2 = 0 then ( x :: pair ), impair else pair, ( x :: impair );;


(* Exercice 4: *)

(* 1: *)
type ensemble = Empty_set | Element of int * ensemble | Intervalle of int * int * ensemble;;

(* 2: *)
let rec intersec e1 e2 =
    let rec element_dans_ensemble x e = match e with
    | Empty_set -> false
    | Element ( y, reste ) -> if x = y then true else element_dans_ensemble x reste
    | Intervalle ( min, max, reste ) -> if ( min <= x && x <= max ) then
        true else element_dans_ensemble x reste
    and intervalle_dans_ensemble min max e = match e with
    | Empty_set -> false
    | Element ( y, reste ) -> if ( min <= y && y <= max ) then
        true else intervalle_dans_ensemble min max reste
    | Intervalle ( min2, max2, reste ) -> if ( min2 <= max || min <= max2 ) then
        true else intervalle_dans_ensemble min max reste
    in match e1 with
    | Empty_set -> false
    | Element ( x, reste ) -> if element_dans_ensemble x e2 then
        true else intersec reste e2
    | Intervalle ( min, max, reste ) -> if intervalle_dans_ensemble min max e2 then
        true else intersec reste e2;;


(* Printf.printf "%b\n" ( let e1 = Element ( 1, Empty_set ) and e2 = Intervalle ( 2, 5, Empty_set ) in intersec e1 e2 );; *)
