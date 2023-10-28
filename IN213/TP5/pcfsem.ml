open Pcfast ;;

type pcfval =
  | Intval of int
  | Boolval of bool
  | Stringval of string
  | Funval of (pcfval -> pcfval)
;;

let rec printval = function
  | Intval n -> Printf.printf "%d" n
  | Boolval b -> Printf.printf "%s" (if b then "T" else "F")
  | Stringval s -> Printf.printf "\"%s\"" s
  | Funval f -> Printf.printf "<fun>"
;;

type env = string -> pcfval ;;

let init_env id =
  raise (Failure (Printf.sprintf "Unbound ident: %s" id))
;;

let extend env x v =
  fun y -> if x = x then v else env y;;

let rec semant e rho =
  match e with
  | Int n -> Intval n
  | Bool b -> Boolval b
  | String s -> Stringval s
  | Ident v -> rho v
  | App ( e1, e2 ) -> (
    match semant e1 rho with
    | Funval f -> f( semant e2 rho )
    | _ -> raise ( Failure "Opération non supportée" )
  )
  | Monop("-", e) -> raise ( Failure "Opération non supportée" )
  | Monop (op, _) -> raise ( Failure "Opérateur non supporté" )
  | Binop (op, e1, e2) -> (
    let v1 = semant e1 rho in
    let v2 = semant e2 rho in
    match ( v1, v2 ) with
      | ( Intval i1, Intval i2 ) -> (
        match op with
          | "+" -> Intval ( i1 + i2 )
          | "-" -> Intval ( i1 - i2 )
          | "*" -> Intval ( i1 * i2 )
          | "/" -> Intval ( i1 / i2 )
          | _ -> raise ( Failure "Opérateur non supporté" )
        )
      | _ -> raise ( Failure "Opération non supportée" )
    )
  | If ( e, e1, e2 ) -> if ( ( semant e rho ) == Boolval true ) then ( semant e1 rho ) else ( semant e2 rho )
  | Fun ( a, e ) -> Funval ( fun v -> semant e ( extend rho a v ) )
  | Let ( x, e1, e2 ) -> semant e2 ( extend rho x ( semant e1 rho ) )
  | Letrec (f, e1, e2) -> (
    let rec rho_ x = extend rho f ( semant e1 rho_ ) x in
    semant e2 rho_
  )
;;

let eval e = semant e init_env ;;
