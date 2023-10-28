(* La mémoire globale. Initialement de taille 256, au hasard, remplie avec la
   valeur 0. S'il n'y a vraiment plus de place, on devrait réallouer de la
   mémoire. Pour simplifier, ici, on échouera simplement. *)
let mem = {
  VmBytecode.size = 256 ;   (* Chaque tas fait initialement 256. *)
  VmBytecode.next_free = 0 ;
  VmBytecode.heap_base = 0 ; (* Sera 0 ou size pour dire dans quel tas on
                                alloue. *)
  (* Comme on a 2 tas, on alloue le tableau de 2 fois la taille. *)
  VmBytecode.data = Array.make (2 * 256) (VmBytecode.VMV_int 0)
} ;;


(* Compteur global permettant, lors de la phase de copie, de savoir où l'on
   doit copier dans le tas destination. C'est plus simple de l'avoir en
   global plutôt que de devoir se trimbaler cet index partout.
   ATTENTION: doit être réinitialisé en début de GC, à la valeur de base
   du tas destination de la copie. *)
let next_free_in_to = ref 0 ;;


(* from_addr = addresse de bloc. On récupère la taille dans la case
   précédente. *)
let copy_block from_addr block_size =
  raise (Failure "à compléter : copy_block")
;;


(* Transfère la mémoire se trouvant à [addr] dans le tas TO si ça n'a pas
   déjà été fait et met un pointeur distant dans le bloc dans le tas FROM.
   Pour savoir si le bloc se trouvant à [addr] a déjà été transféré, il
   suffit de regarder s'il contient une adresse distante, donc si dans
   mem[addr] on trouve une VMV_addr désignant une adresse dans le bloc TO. *)
let rec transfer_pointer addr =
  raise (Failure "à compléter : transfer_pointer")
;;


(* Copie des racines. Retourne la valeur de la nouvelle racine et déclenche
   Si nécessaire la copie et le relogement de pointeur si la racine en est
   un. *)
let copy_root v =
  raise (Failure "à compléter : copy_root")
;;


(* Déclenchement du GC. *)
let gc vm_state =
  raise (Failure "à compléter : gc")
;;


(* Allocation d'un bloc mémoire de taille donnée. S'il n'y a plus assez de
   mémoire dans le tas, déclenche un GC. *)
let new_block vm_state alloc_size =
  (* L'allocation effective sera de 1 de plus pour pouvoir mémoriser
     la taille du bloc. *)
  let vm_state' =
    if (mem.next_free - mem.heap_base) + alloc_size + 1 >= mem.size then (
      (* Besoin de déclencher un GC car plus assez de mémoire. *)
      let state = gc vm_state in
      (* On vérifie s'il reste bien de la mémoire après le GC, sinon on
         échoue. On fait une version simplifiée qui ne réalloue pas de tas. *)
      if (mem.next_free - mem.heap_base) + alloc_size + 1 >= mem.size then
        raise (Failure "Really no more memory") ;
      state
     )
    else vm_state in
  (* L'adresse du bloc est celle juste après son champ de taille. C'est cette
     adresse que l'on retourne à "l'utilisateur". *)
  let tmp = mem.next_free + 1 in
  (* On mémorise la taille du bloc. *)
  mem.data.(mem.next_free) <- VmBytecode.VMV_int alloc_size ;
  (* On fait progresser l'indice de prochain bloc libre. Comme on a pris une
     case pour mettre la taille du bloc, il ne faut pas oublier le + 1. *)
  mem.next_free <- mem.next_free + alloc_size + 1 ;
  (* On retourne l'adresse du bloc alloué. *)
  (tmp, vm_state')
;;
