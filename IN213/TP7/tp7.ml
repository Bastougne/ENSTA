type term =
  | Var of string
  | Term of string * term list;;

let zero = Term ("Zero", [ ]) ;;
let succ t = Term ("Succ", [t]) ;;
let plus (t1,t2) = Term ("Plus", [t1; t2]) ;;
let x = Var "x" and y = Var "y" and z = Var "z" ;;


let rec vars_term t accu =
  match t with
    | Var v -> v :: accu
    | Term ( _, tlist ) -> vars_list_terms tlist accu

and vars_list_terms l accu =
  match l with
    | [] -> accu
    | t :: rem -> let accu_ = vars_term t accu in
      vars_list_terms rem accu_;;

let vars t =
  vars_term t [];;


type subst = ( string * term ) list;;

let rec image x ( s : subst ) = match s with
  | [] -> Var x
  | ( y, t ) :: rem -> if x = y then t else image x rem;;


let is_in_dom v mu =
  ( image v mu ) = v;;

let rec moins_subst theta mu = match theta with
  | [] -> []
  | ( v, t ) :: rem -> if is_in_dom v mu then moins_subst rem mu else ( v, t ) :: moins_subst rem mu;;

let compose theta2 theta1 =
  let theta List.map ( fun ( v, t ) -> ( v, appsubst theta2 t ) ) theta1 in
  let mu = moins_subst theta2 theta1 in theta @ mu;;


let rec filtrage paires theta = match paires with
  | [] -> theta
  | ( Var x, t1 ) :: rem -> ( match image x with
    | Var y when x = y -> filtrage rem ( ( x, t1 ) :: theta )
    | t2 -> if t2 = t1 then filtrage rem theta else raise ( Failure "échec" )
    | ( Term ( s1, tl1 ), Term ( s2, tl2 ) :: rem -> if s1 = s2 then
      filtrage ( ( List.combine tl1 tl2 ) @ rem ) theta else raise ( Failure "échec" )
    | _ -> raise ( Failure "échec" );;