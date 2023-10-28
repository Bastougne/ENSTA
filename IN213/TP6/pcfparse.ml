type token =
  | INT of (int)
  | IDENT of (string)
  | TRUE
  | FALSE
  | STRING of (string)
  | PLUS
  | MINUS
  | MULT
  | DIV
  | EQUAL
  | GREATER
  | SMALLER
  | GREATEREQUAL
  | SMALLEREQUAL
  | LPAR
  | RPAR
  | SEMISEMI
  | LET
  | REC
  | IN
  | FUN
  | ARROW
  | IF
  | THEN
  | ELSE

open Parsing;;
let _ = parse_error;;
# 2 "pcfparse.mly"
open Pcfast ;;

let rec mkfun params expr =
  match params with
  | [] -> expr
  | p :: prms -> EFun(p, mkfun prms expr)
;;
# 39 "pcfparse.ml"
let yytransl_const = [|
  259 (* TRUE *);
  260 (* FALSE *);
  262 (* PLUS *);
  263 (* MINUS *);
  264 (* MULT *);
  265 (* DIV *);
  266 (* EQUAL *);
  267 (* GREATER *);
  268 (* SMALLER *);
  269 (* GREATEREQUAL *);
  270 (* SMALLEREQUAL *);
  271 (* LPAR *);
  272 (* RPAR *);
  273 (* SEMISEMI *);
  274 (* LET *);
  275 (* REC *);
  276 (* IN *);
  277 (* FUN *);
  278 (* ARROW *);
  279 (* IF *);
  280 (* THEN *);
  281 (* ELSE *);
    0|]

let yytransl_block = [|
  257 (* INT *);
  258 (* IDENT *);
  261 (* STRING *);
    0|]

let yylhs = "\255\255\
\001\000\001\000\002\000\002\000\002\000\002\000\002\000\003\000\
\003\000\004\000\004\000\004\000\004\000\004\000\004\000\004\000\
\004\000\004\000\004\000\005\000\005\000\005\000\006\000\006\000\
\006\000\006\000\006\000\006\000\000\000"

let yylen = "\002\000\
\002\000\002\000\009\000\007\000\004\000\006\000\001\000\002\000\
\000\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\001\000\002\000\002\000\001\000\001\000\001\000\
\001\000\001\000\001\000\003\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\023\000\027\000\024\000\025\000\026\000\000\000\
\000\000\000\000\000\000\000\000\000\000\029\000\000\000\000\000\
\000\000\022\000\021\000\000\000\002\000\000\000\000\000\000\000\
\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\020\000\028\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\017\000\018\000\000\000\000\000\
\000\000\000\000\000\000\008\000\000\000\000\000\005\000\000\000\
\000\000\000\000\000\000\000\000\000\000\006\000\004\000\000\000\
\000\000\003\000"

let yydgoto = "\002\000\
\014\000\015\000\039\000\016\000\017\000\018\000"

let yysindex = "\002\000\
\004\255\000\000\000\000\000\000\000\000\000\000\000\000\179\255\
\013\255\004\255\010\255\011\255\013\255\000\000\006\255\193\255\
\179\255\000\000\000\000\008\255\000\000\028\255\033\255\015\255\
\024\255\000\000\172\255\172\255\172\255\172\255\172\255\172\255\
\172\255\172\255\172\255\000\000\000\000\028\255\045\255\064\255\
\013\255\013\255\249\254\249\254\000\000\000\000\211\255\211\255\
\211\255\211\255\211\255\000\000\013\255\028\255\000\000\044\255\
\050\255\062\255\013\255\013\255\013\255\000\000\000\000\065\255\
\013\255\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\173\255\
\051\255\000\000\000\000\000\000\000\000\072\255\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\072\255\000\000\000\000\
\000\000\000\000\067\255\083\255\000\000\000\000\029\255\099\255\
\115\255\131\255\147\255\000\000\000\000\072\255\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000"

let yygindex = "\000\000\
\076\000\247\255\228\255\181\000\000\000\030\000"

let yytablesize = 220
let yytable = "\020\000\
\029\000\030\000\001\000\025\000\003\000\004\000\005\000\006\000\
\007\000\052\000\008\000\022\000\024\000\003\000\004\000\005\000\
\006\000\007\000\009\000\008\000\010\000\011\000\026\000\037\000\
\012\000\058\000\013\000\009\000\023\000\038\000\011\000\055\000\
\056\000\012\000\040\000\013\000\041\000\019\000\010\000\010\000\
\010\000\010\000\010\000\057\000\010\000\010\000\036\000\042\000\
\010\000\062\000\063\000\064\000\010\000\010\000\053\000\066\000\
\019\000\019\000\019\000\019\000\019\000\019\000\019\000\019\000\
\019\000\054\000\019\000\019\000\059\000\060\000\019\000\061\000\
\015\000\015\000\019\000\019\000\015\000\015\000\015\000\015\000\
\015\000\009\000\015\000\015\000\065\000\021\000\015\000\000\000\
\016\000\016\000\015\000\015\000\016\000\016\000\016\000\016\000\
\016\000\000\000\016\000\016\000\000\000\000\000\016\000\000\000\
\000\000\000\000\016\000\016\000\011\000\011\000\011\000\011\000\
\011\000\000\000\011\000\011\000\000\000\000\000\011\000\000\000\
\000\000\000\000\011\000\011\000\013\000\013\000\013\000\013\000\
\013\000\000\000\013\000\013\000\000\000\000\000\013\000\000\000\
\000\000\000\000\013\000\013\000\012\000\012\000\012\000\012\000\
\012\000\000\000\012\000\012\000\000\000\000\000\012\000\000\000\
\000\000\000\000\012\000\012\000\014\000\014\000\014\000\014\000\
\014\000\000\000\014\000\014\000\000\000\000\000\014\000\000\000\
\000\000\000\000\014\000\014\000\003\000\004\000\005\000\006\000\
\007\000\000\000\008\000\003\000\004\000\005\000\006\000\007\000\
\000\000\000\000\009\000\000\000\007\000\007\000\000\000\000\000\
\007\000\009\000\000\000\000\000\007\000\007\000\027\000\028\000\
\029\000\030\000\031\000\032\000\033\000\034\000\035\000\043\000\
\044\000\045\000\046\000\047\000\048\000\049\000\050\000\051\000\
\027\000\028\000\029\000\030\000"

let yycheck = "\009\000\
\008\001\009\001\001\000\013\000\001\001\002\001\003\001\004\001\
\005\001\038\000\007\001\002\001\002\001\001\001\002\001\003\001\
\004\001\005\001\015\001\007\001\017\001\018\001\017\001\016\001\
\021\001\054\000\023\001\015\001\019\001\002\001\018\001\041\000\
\042\000\021\001\002\001\023\001\022\001\008\000\010\001\011\001\
\012\001\013\001\014\001\053\000\016\001\017\001\017\000\024\001\
\020\001\059\000\060\000\061\000\024\001\025\001\010\001\065\000\
\006\001\007\001\008\001\009\001\010\001\011\001\012\001\013\001\
\014\001\002\001\016\001\017\001\025\001\020\001\020\001\010\001\
\006\001\007\001\024\001\025\001\010\001\011\001\012\001\013\001\
\014\001\010\001\016\001\017\001\020\001\010\000\020\001\255\255\
\006\001\007\001\024\001\025\001\010\001\011\001\012\001\013\001\
\014\001\255\255\016\001\017\001\255\255\255\255\020\001\255\255\
\255\255\255\255\024\001\025\001\010\001\011\001\012\001\013\001\
\014\001\255\255\016\001\017\001\255\255\255\255\020\001\255\255\
\255\255\255\255\024\001\025\001\010\001\011\001\012\001\013\001\
\014\001\255\255\016\001\017\001\255\255\255\255\020\001\255\255\
\255\255\255\255\024\001\025\001\010\001\011\001\012\001\013\001\
\014\001\255\255\016\001\017\001\255\255\255\255\020\001\255\255\
\255\255\255\255\024\001\025\001\010\001\011\001\012\001\013\001\
\014\001\255\255\016\001\017\001\255\255\255\255\020\001\255\255\
\255\255\255\255\024\001\025\001\001\001\002\001\003\001\004\001\
\005\001\255\255\007\001\001\001\002\001\003\001\004\001\005\001\
\255\255\255\255\015\001\255\255\016\001\017\001\255\255\255\255\
\020\001\015\001\255\255\255\255\024\001\025\001\006\001\007\001\
\008\001\009\001\010\001\011\001\012\001\013\001\014\001\027\000\
\028\000\029\000\030\000\031\000\032\000\033\000\034\000\035\000\
\006\001\007\001\008\001\009\001"

let yynames_const = "\
  TRUE\000\
  FALSE\000\
  PLUS\000\
  MINUS\000\
  MULT\000\
  DIV\000\
  EQUAL\000\
  GREATER\000\
  SMALLER\000\
  GREATEREQUAL\000\
  SMALLEREQUAL\000\
  LPAR\000\
  RPAR\000\
  SEMISEMI\000\
  LET\000\
  REC\000\
  IN\000\
  FUN\000\
  ARROW\000\
  IF\000\
  THEN\000\
  ELSE\000\
  "

let yynames_block = "\
  INT\000\
  IDENT\000\
  STRING\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 28 "pcfparse.mly"
                    ( _1 )
# 221 "pcfparse.ml"
               : Pcfast.expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Pcfast.expr) in
    Obj.repr(
# 29 "pcfparse.mly"
                    ( _2 )
# 228 "pcfparse.ml"
               : Pcfast.expr))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 6 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 5 : string) in
    let _5 = (Parsing.peek_val __caml_parser_env 4 : 'seqident) in
    let _7 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _9 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 36 "pcfparse.mly"
         ( ELetrec (_3, _4, (mkfun _5 _7), _9) )
# 239 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 5 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'seqident) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 38 "pcfparse.mly"
         ( ELet (_2, (mkfun _3 _5) , _7) )
# 249 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 2 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 40 "pcfparse.mly"
         ( EFun (_2, _4) )
# 257 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 42 "pcfparse.mly"
         ( EIf (_2, _4, _6) )
# 266 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 44 "pcfparse.mly"
         ( _1 )
# 273 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : string) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'seqident) in
    Obj.repr(
# 48 "pcfparse.mly"
                  ( _1 :: _2 )
# 281 "pcfparse.ml"
               : 'seqident))
; (fun __caml_parser_env ->
    Obj.repr(
# 49 "pcfparse.mly"
                  ( [] )
# 287 "pcfparse.ml"
               : 'seqident))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 53 "pcfparse.mly"
                                     ( EBinop ("=", _1, _3) )
# 295 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 54 "pcfparse.mly"
                                     ( EBinop (">", _1, _3) )
# 303 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 55 "pcfparse.mly"
                                     ( EBinop (">=", _1, _3) )
# 311 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 56 "pcfparse.mly"
                                     ( EBinop ("<", _1, _3) )
# 319 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 57 "pcfparse.mly"
                                     ( EBinop ("<=", _1, _3) )
# 327 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 58 "pcfparse.mly"
                                     ( EBinop ("+", _1, _3) )
# 335 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 59 "pcfparse.mly"
                                     ( EBinop ("-", _1, _3) )
# 343 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 60 "pcfparse.mly"
                                     ( EBinop ("*", _1, _3) )
# 351 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 61 "pcfparse.mly"
                                     ( EBinop ("/", _1, _3) )
# 359 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'application) in
    Obj.repr(
# 62 "pcfparse.mly"
                                     ( _1 )
# 366 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'application) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'atom) in
    Obj.repr(
# 72 "pcfparse.mly"
                   ( EApp (_1, _2) )
# 374 "pcfparse.ml"
               : 'application))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'atom) in
    Obj.repr(
# 73 "pcfparse.mly"
                   ( EMonop ("-", _2) )
# 381 "pcfparse.ml"
               : 'application))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'atom) in
    Obj.repr(
# 74 "pcfparse.mly"
                   ( _1 )
# 388 "pcfparse.ml"
               : 'application))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 78 "pcfparse.mly"
                 ( EInt (_1) )
# 395 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    Obj.repr(
# 79 "pcfparse.mly"
                 ( EBool (true) )
# 401 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    Obj.repr(
# 80 "pcfparse.mly"
                 ( EBool (false) )
# 407 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 81 "pcfparse.mly"
                 ( EString (_1) )
# 414 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 82 "pcfparse.mly"
                 ( EIdent (_1) )
# 421 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 83 "pcfparse.mly"
                 ( _2 )
# 428 "pcfparse.ml"
               : 'atom))
(* Entry main *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let main (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Pcfast.expr)
