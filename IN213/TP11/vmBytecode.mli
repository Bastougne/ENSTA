type vm_code = vm_instr list

and vm_instr =
  | VMI_Loadi of int
  | VMI_Loadb of bool
  | VMI_Loads of string
  | VMI_Plus | VMI_Sub
  | VMI_Mult | VMI_Div
  | VMI_Equal
  | VMI_Read of int
  | VMI_Indxread
  | VMI_Branch of (vm_code * vm_code)
  | VMI_Loop of (vm_code * vm_code)
  | VMI_Push
  | VMI_Pushenv
  | VMI_Pop
  | VMI_Popenv
  | VMI_Call of string
  | VMI_Return
  | VMI_Envext
  | VMI_Assign of int
  | VMI_Indxwrite
  | VMI_Print
  | VMI_Mkblock
  | VMI_Lt
  | VMI_Le
  | VMI_Gt
  | VMI_Ge
;;

type vm_val =
  | VMV_int of int
  | VMV_bool of bool
  | VMV_string of string
  | VMV_addr of address
  | VMV_code_addr of vm_code
  | VMV_env of vm_env

and address = int
and vm_env = address list ;;

type vm_stack = vm_val list ;;

type mem = {
  mutable size : int ;          (* Taille d'un seul tas. *)
  mutable next_free : int ;     (* Adresse prochain bloc libre. *)
  mutable heap_base : int ;     (* Adresse de début du tas courant.
        Idéalement, seul le module Mem doit s'en occuper. Dans les faits,
        afin de vérifier les accès en dehors de la mémoire, VmExec a besoin
        de connaître cette valeur afin de vérifier qu'une adresse est bien
        inférieure à la taille de la zone mémoire. *)
  mutable data : vm_val array } (* Les 2 tas, donc de taille size * 2. *)
;;

type vm_state = {
  register : vm_val ;
  code : vm_code ;
  stack : vm_stack ;
  env : vm_env
} ;;
