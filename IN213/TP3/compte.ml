(* Programme principal.
 * Ne fait que compter les caracteres.
 * Utilise une fonction count appartenant a un module Cptlex que vous
 * definirez par un analyseur count dans un fichier cptlex.mll.
 *)

let count filename =
  try
    let input = open_in filename in
    let lexbuf = Lexing.from_channel input in
    let ( nbchars, nbwords, nblines ) = Cptlex.count 0 0 0 lexbuf in
    Printf.printf
      "%s: %d caractere(s), %d mot(s), %d lignes(s)\n%!"
      filename nbchars nbwords nblines ;
    close_in input
  with
  | Sys_error msg ->
      Printf.eprintf "Impossible d'ouvrir \"%s\" (%s)\n%!" filename msg
  | err ->
      Printf.eprintf "Exception inattendue %s\n%!" (Printexc.to_string err)
;;

let main() =
  for i = 1 to (Array.length Sys.argv) - 1 do
    count Sys.argv.(i)
  done;
  exit 0
;;

if !Sys.interactive then () else main () ;;
