exception Unbound_identifier of string ;;


(* Find the position of an element in a list, with position 0 being the
   head of the list. *)
let rec find_pos x = function
  | [] -> raise Not_found
  | h :: q -> if h = x then 0 else 1 + (find_pos x q)
;;


(* Évaluation d'une expression. La mémoire est implicite puisque globale. *)
let rec compile_expr rho = function
  | Impast.Int i -> [ VmBytecode.VMI_Loadi i ]
  | Impast.Bool b -> [ VmBytecode.VMI_Loadb b ]
  | Impast.String s -> [ VmBytecode.VMI_Loads s ]
  | Impast.Ident id ->
      let pos =
        (try find_pos id rho with Not_found -> raise (Unbound_identifier id)) in
      [VmBytecode.VMI_Read pos]
  | Impast.ArrayRead (id, e_index) ->
      (* Réupérer la position du pointeur dans l'environnement. *)
      let pos =
        (try find_pos id rho with Not_found -> raise (Unbound_identifier id)) in
      (* Récupérer la valeur du pointeur (i.e. adresse de base du tableau) dans
         le registre et la mettre sur la pile. *)
      let array_base_code =
        [(VmBytecode.VMI_Read pos) ; VmBytecode.VMI_Push ] in
      let e_index_code = compile_expr rho e_index in
      (* L'indice où aller lire est dans le registre. *)
      array_base_code @ e_index_code @ [VmBytecode.VMI_Indxread]
  | Impast.App (f_name, args) -> compile_app rho f_name args
  | Impast.Monop (o_name, e) -> (
      match o_name with
      | "-" ->
          (* Translate to 0 - e. *)
          let translation = Impast.Binop ("-", (Impast.Int 0), e) in
          compile_expr rho translation
      | _ -> raise (Failure "Unknown monop")
     )
  | Impast.Binop (o_name, e1, e2) ->
      (* Get the virtual machine instruction depending on the operator. *)
      let binop_instr =
        (match o_name with
        | "+" -> VmBytecode.VMI_Plus
        | "-" -> VmBytecode.VMI_Sub
        | "*" -> VmBytecode.VMI_Mult
        | "/" -> VmBytecode.VMI_Div
        | "==" -> VmBytecode.VMI_Equal
        | "<" -> VmBytecode.VMI_Lt
        | "<=" -> VmBytecode.VMI_Le
        | ">" -> VmBytecode.VMI_Gt
        | ">=" -> VmBytecode.VMI_Ge
        | _ -> raise (Failure "Unknown binop")) in
      let e1_code = compile_expr rho e1 in
      let e2_code = compile_expr rho e2 in
        (e1_code @ [VmBytecode.VMI_Push] @ e2_code @ [binop_instr])


and compile_app_args rho = function
  | [] -> []
  | h :: q ->
      (* Crée le bloc pour le paramètre. *)
      let mk_block_code =
        [VmBytecode.VMI_Loadi 1 ; VmBytecode.VMI_Mkblock ;
         VmBytecode.VMI_Envext] in
      (* Compile l'argument effectif. Le fait d'avoir mis le bloc correspondant
         à l'argument effectif dans l'environnement fait que l'on décale d'1
         les indices des variables locales de la fonction courante. Si la
         compilation des arguments a besoin d'accéder à un identificateur, il
         faut corriger ça. On va donc rajouter dans notre environement de
         compilation une liaison factice. C'est ça ou l'on doit conserver un
         compteur de décalage que l'on va se trimbaler à chaque appel à
         compil_*. *)
      let adjusted_rho = ("" :: rho) in
      let arg_code = compile_expr adjusted_rho h in
      (* Affecte la valeur de l'argument effectif dans le bloc. Le bloc est
         forcément le numéro 0 puisque c'est celui que l'on vient de créer. *)
      let assign_code = [VmBytecode.VMI_Assign 0] in
       mk_block_code @ arg_code @ assign_code @
      (compile_app_args adjusted_rho q)


and compile_app rho f_name args =
  (* Compile les arguments effectifs. *)
  let args_code = compile_app_args rho args in
  (* VMI_Call va sauvegarder le code restant à exécuter sur la pile et va
     le remplacer par celui de la fonction appelée. *)
  [VmBytecode.VMI_Pushenv] @ args_code @
  [VmBytecode.VMI_Call f_name ; VmBytecode.VMI_Popenv]


and compile_instr rho = function
  | Impast.While (e, i) ->
      let e_code = compile_expr rho e in
      let i_code = compile_instr rho i in
      e_code @ [VmBytecode.VMI_Loop (e_code, i_code)]
  | Impast.If (e, i1, i2) ->
      let e_code = compile_expr rho e in
      let i1_code = compile_instr rho i1 in
      let i2_code = compile_instr rho i2 in
       e_code @ [VmBytecode.VMI_Branch (i1_code, i2_code)]
  | Impast.Assign (id, e) ->
      (* Compilation valeur à stocker -> registre *)
      let e_code = compile_expr rho e in
      let pos =
        (try find_pos id rho with Not_found -> raise (Unbound_identifier id)) in
      e_code @ [VmBytecode.VMI_Assign pos]
  | Impast.Seq (i1, i2) ->
      let i1_code = compile_instr rho i1 in
      let i2_code = compile_instr rho i2 in
      i1_code @ i2_code
  | Impast.Return e_opt ->
      let e_code =
        (match e_opt with None -> [] | Some e -> compile_expr rho e) in
      e_code @ [VmBytecode.VMI_Return]
  | Impast.Iapp (f_name, args) -> compile_app rho f_name args
  | Impast.Print args ->
      (*
        L'utilisation de List.fold_right est équivalente à écrire la fonction
        récusrive suivante et à l'appliquer à args.
        8< ------------------------------------------------- >8
             let rec compile_print_args rho args =
               match args with
               | [] -> []
               | arg :: rem ->
                   let code = compile_expr rho arg in
                   let rem_code = compile_print_args rho rem in
                   code @ [VmBytecode.VMI_Print] @ rem_code
        8< ------------------------------------------------- >8
      *)
      List.fold_right
        (fun e accu -> (compile_expr rho e) @ [ VmBytecode.VMI_Print] @ accu)
        args []
  | Impast.ArrayWrite (id, e1, e2) ->
       (* Récupérer la valeur du pointeur (i.e. adresse de base du tableau)
          dans le registre et la mettre sur la pile. *)
      let pos =
        (try find_pos id rho with Not_found -> raise (Unbound_identifier id)) in
      let array_base_code =
        [(VmBytecode.VMI_Read pos) ; VmBytecode.VMI_Push] in
      (* Compiler la valeur à stocker et la mettre sur la pile. *)
      let e2_code = (compile_expr rho e2) @ [VmBytecode.VMI_Push] in
      (* Compiler l'indice où aller écrire -> registre *)
      let e1_code = compile_expr rho e1 in
      (* La valeur de l'index se trouve dans l'accumulateur. La valeur à
         affecter est au sommet de la pile, l'adresse où écrire juste en
       dessous. *)
      array_base_code @ e2_code @ e1_code @ [VmBytecode.VMI_Indxwrite]


and compile_var_decls rho = function
  | [] -> (rho, [])
  | (v_name, decl) :: q ->
      let decl_code =
        (match decl with
        | Impast.Scalar ->
            (* Pas la peine de sauvegarder le registre car les déclarations de
               variables se font au toplevel ou en début de fonction, donc sans
               calculs en suspens. *)
            [VmBytecode.VMI_Loadi 1; VmBytecode.VMI_Mkblock;
             VmBytecode.VMI_Envext]
        | Impast.Array e ->
            (* Compilation de la taille. Comme on n'a pas encore étendu
               l'environnement d'exécution avec le pointeur alloué pour le
               tableau (il est alloué juste après le calcul de la taille du
               tableau), on n'a pas besoin d'insérer de liaison factice dans
               l'environnement de compilation. *)
            let e_code = compile_expr rho e in
            (* Allocation de la variable pointeur (pas encore de la zone
               mémoire). Il faut sauvegarder la taille à allouer car on va
               écraser le registre. *)
            let ptr_code =
              [VmBytecode.VMI_Push ; VmBytecode.VMI_Loadi 1 ;
               VmBytecode.VMI_Mkblock; VmBytecode.VMI_Envext] in
            (* Allocation de la zone mémoire du tableau. Il faut récupérer la
               taille et la mettre dans le registre. *)
            let alloc_code = [VmBytecode.VMI_Pop ; VmBytecode.VMI_Mkblock] in
            (* Il faut affecter le pointeur précédemment alloué avec l'adresse
               de la zone que l'on vient d'allouer. Ce pointeur est la dernière
               variable créée, donc d'indice 0 dans l'environnement. *)
            e_code @ ptr_code @ alloc_code @ [VmBytecode.VMI_Assign 0]) in
      let (rho', q_code) = compile_var_decls (v_name :: rho) q in
      (rho', (decl_code @ q_code))
;;


type object_code = {
  (* Définitions globales toplevel à exécuter au tout début du programme. *)
  global : VmBytecode.vm_code ;
  (* Code de chacune des fonctions. *)
  funs : (string * VmBytecode.vm_code) list
} ;;


(* Nature du bytecode généré. Le code provenant de déclarations de variables
   globales est regroupé en début de bytecode. *)
type toplevel_code =
  | TC_Global of VmBytecode.vm_code
  | TC_Fun of (string * VmBytecode.vm_code)
;;


let compile_toplevel rho = function
  | Impast.Vardecl v_decl ->
      let (rho', var_code) =  compile_var_decls rho [v_decl] in
       (rho', (TC_Global var_code))
  | Impast.Fundef f_def ->
      (* Penser à inverser la list des paramètres car on les empile dans
         l'environnement. *)
      let rho' = (List.rev f_def.Impast.params) @ rho in
      let (rho'', vars_code) = compile_var_decls rho' f_def.Impast.vars in
      (* Compilation du corps de la fonction. *)
      let body_code = compile_instr rho'' f_def.Impast.body in
      (* On joint le code des déclarations de variables locales et celui du
         corps de la fonction. *)
      let all_code = vars_code @ body_code in
      (* L'environnement reste inchangé au final car les fonctions ne sont pas
         liées dans l'environnement. *)
      (rho, (TC_Fun (f_def.Impast.f_name, all_code)))
;;


let rec compile_program rho = function
  | [] -> { global = [] ; funs = [] }
  | h :: q -> (
      let (rho', code) = compile_toplevel rho h in
      let rem_code = compile_program rho' q in
      match code with
      | TC_Global c -> { global = c @ rem_code.global ; funs = rem_code.funs }
      | TC_Fun c -> { global = rem_code.global ; funs = c :: rem_code.funs }
     )
;;


(* Exécutable final, avec le point d'entrée identifié et la liste de toutes
   les fonctions du programme avec leur code.
   Le point d'entrée correspond au code des déclarations de variables globales
   suivi du code de main. *)
type executable = {
  entry_point : VmBytecode.vm_code ;
  funs_codes : (string * VmBytecode.vm_code) list
} ;;


let make_executable obj_code =
  (* On recherche le code du main. *)
  let main_code =
    (try List.assoc "main" obj_code.funs with
    | Not_found -> raise (Failure "Main not defined")) in
  let whole_code = obj_code.global @ main_code in
  { entry_point = whole_code ; funs_codes = obj_code.funs }
;;
