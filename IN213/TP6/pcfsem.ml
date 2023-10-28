open Pcfast;;

type pcfval =
  | Intval of int
  | Boolval of bool
  | Stringval of string
  | Funval of { param: string; body: expr; env: environment }
  | Funrecval of { fname: string; param: string; body: expr; env: environment }

and environment = (string * pcfval) list
;;

let rec printval = function
  | Intval n -> Printf.printf "%d" n
  | Boolval b -> Printf.printf "%s" (if b then "true" else "false")
  | Stringval s -> Printf.printf "%S" s
  | Funval _ -> Printf.printf "<fun>"
  | Funrecval _ -> Printf.printf "<fun rec>"
;;

(* Environnement. *)
let init_env = [] ;;

let error msg = raise(Failure msg) ;;

let extend rho x v = (x, v) :: rho ;;

let lookup var_name rho =
  try List.assoc var_name rho
  with Not_found -> error (Printf.sprintf "Undefined ident '%s'" var_name)
;;


(* Fonction "bouche-trou". *)
let afinir () = Stringval "A FINIR" ;;


let rec eval e rho =
  match e with
  | EInt n -> Intval n
  | EBool b -> Boolval b
  | EString s -> Stringval s
  | EIdent v -> lookup v rho
  | EApp (e1, e2) -> (
      match eval e1 rho with
        | Funval {param = x; body = e0} -> (
            eval e0 ( extend rho x ( eval e2 rho ) )
          )
        | _ -> raise ( Failure "Pas une fonction" )
    )
  | EMonop ( "-", e ) -> (
      match eval e rho with
      | Intval i -> Intval ( -i )
      | _ -> raise ( Failure "Opération non supportée" )
    )
  | EMonop ( op, _ ) -> error ( Printf.sprintf "Unknown unary op: %s" op )
  | EBinop (op, e1, e2) -> (
      let v1 = eval e1 rho in
      let v2 = eval e2 rho in
      match ( v1, v2 ) with
      | ( Intval i1, Intval i2 ) -> (
        match op with
          | "+" -> Intval ( i1 + i2 )
          | "-" -> Intval ( i1 - i2 )
          | "*" -> Intval ( i1 * i2 )
          | "/" -> Intval ( i1 / i2 )
          | "<=" -> if ( i1 <= i2 ) then Boolval true else Boolval false
          | _ -> raise ( Failure "Opérateur non supporté" )
        )
      | _ -> raise ( Failure "Opération non supportée" )
    )
  | EIf ( e, e1, e2 ) -> (
      match eval e rho with
      | Boolval true -> eval e1 rho
      | Boolval false -> eval e2 rho
      | _ -> raise ( Failure "Condition non booléenne" )
    )
  | EFun (a, e) -> Funval { param = a; body = e; env = rho }
  | ELet (x, e1, e2) -> eval e2 ( extend rho x ( eval e1 rho ) )
  | ELetrec (f, x, e1, e2) -> (
      let f1 = Funrecval { fname = f; param = x; body = e1; env = rho } in
      eval e2 ( extend rho f f1 )
    )
;;

let eval e = eval e init_env ;;
