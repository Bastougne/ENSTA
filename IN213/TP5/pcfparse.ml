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
  | LETREC
  | IN
  | FUN
  | ARROW
  | IF
  | THEN
  | ELSE

open Parsing;;
let _ = parse_error;;
# 2 "pcfparse.mly"
  open Pcfast;;

  let rec body params expr = match params with
  | [] -> expr
  | p :: prms -> Fun(p, body prms expr)
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
  276 (* LETREC *);
  277 (* IN *);
  278 (* FUN *);
  279 (* ARROW *);
  280 (* IF *);
  281 (* THEN *);
  282 (* ELSE *);
    0|]

let yytransl_block = [|
  257 (* INT *);
  258 (* IDENT *);
  261 (* STRING *);
    0|]

let yylhs = "\255\255\
\001\000\002\000\002\000\002\000\002\000\002\000\002\000\004\000\
\004\000\004\000\004\000\004\000\004\000\004\000\004\000\004\000\
\004\000\005\000\005\000\005\000\006\000\006\000\006\000\006\000\
\006\000\006\000\003\000\003\000\000\000"

let yylen = "\002\000\
\002\000\007\000\008\000\007\000\004\000\006\000\001\000\001\000\
\003\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\001\000\002\000\002\000\001\000\001\000\001\000\001\000\
\001\000\003\000\002\000\000\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\021\000\025\000\022\000\023\000\024\000\000\000\
\000\000\000\000\000\000\000\000\000\000\029\000\000\000\000\000\
\000\000\018\000\019\000\000\000\000\000\000\000\000\000\000\000\
\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\020\000\026\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\016\000\017\000\000\000\
\000\000\000\000\000\000\000\000\027\000\000\000\000\000\000\000\
\005\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\006\000\004\000\000\000\002\000\003\000"

let yydgoto = "\002\000\
\014\000\015\000\039\000\016\000\017\000\018\000"

let yysindex = "\001\000\
\004\255\000\000\000\000\000\000\000\000\000\000\000\000\199\255\
\004\255\001\255\008\255\013\255\004\255\000\000\000\255\211\255\
\199\255\000\000\000\000\007\255\025\255\038\255\025\255\002\255\
\017\255\000\000\034\255\034\255\034\255\034\255\034\255\034\255\
\034\255\034\255\034\255\000\000\000\000\025\255\033\255\025\255\
\036\255\004\255\004\255\005\255\005\255\000\000\000\000\023\255\
\023\255\023\255\023\255\023\255\000\000\004\255\040\255\004\255\
\000\000\018\255\027\255\004\255\031\255\004\255\004\255\037\255\
\004\255\000\000\000\000\004\255\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\190\255\
\054\255\000\000\000\000\000\000\045\255\000\000\045\255\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\045\255\000\000\045\255\
\000\000\000\000\000\000\071\255\088\255\000\000\000\000\105\255\
\122\255\139\255\156\255\173\255\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000"

let yygindex = "\000\000\
\000\000\247\255\234\255\199\000\000\000\004\000"

let yytablesize = 234
let yytable = "\020\000\
\041\000\001\000\021\000\025\000\003\000\004\000\005\000\006\000\
\007\000\023\000\008\000\019\000\029\000\030\000\024\000\053\000\
\026\000\055\000\009\000\022\000\036\000\010\000\037\000\011\000\
\042\000\012\000\038\000\013\000\027\000\028\000\029\000\030\000\
\057\000\058\000\003\000\004\000\005\000\006\000\007\000\040\000\
\008\000\043\000\054\000\062\000\059\000\056\000\061\000\063\000\
\009\000\060\000\064\000\065\000\066\000\067\000\028\000\069\000\
\000\000\068\000\070\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\000\000\008\000\008\000\000\000\
\000\000\000\000\008\000\000\000\014\000\014\000\008\000\008\000\
\014\000\014\000\014\000\014\000\014\000\000\000\014\000\014\000\
\000\000\000\000\000\000\014\000\000\000\015\000\015\000\014\000\
\014\000\015\000\015\000\015\000\015\000\015\000\000\000\015\000\
\015\000\000\000\000\000\000\000\015\000\000\000\000\000\000\000\
\015\000\015\000\009\000\009\000\009\000\009\000\009\000\000\000\
\009\000\009\000\000\000\000\000\000\000\009\000\000\000\000\000\
\000\000\009\000\009\000\010\000\010\000\010\000\010\000\010\000\
\000\000\010\000\010\000\000\000\000\000\000\000\010\000\000\000\
\000\000\000\000\010\000\010\000\012\000\012\000\012\000\012\000\
\012\000\000\000\012\000\012\000\000\000\000\000\000\000\012\000\
\000\000\000\000\000\000\012\000\012\000\011\000\011\000\011\000\
\011\000\011\000\000\000\011\000\011\000\000\000\000\000\000\000\
\011\000\000\000\000\000\000\000\011\000\011\000\013\000\013\000\
\013\000\013\000\013\000\000\000\013\000\013\000\000\000\000\000\
\000\000\013\000\000\000\000\000\000\000\013\000\013\000\003\000\
\004\000\005\000\006\000\007\000\000\000\007\000\007\000\000\000\
\000\000\000\000\007\000\000\000\000\000\009\000\007\000\007\000\
\027\000\028\000\029\000\030\000\031\000\032\000\033\000\034\000\
\035\000\044\000\045\000\046\000\047\000\048\000\049\000\050\000\
\051\000\052\000"

let yycheck = "\009\000\
\023\000\001\000\002\001\013\000\001\001\002\001\003\001\004\001\
\005\001\002\001\007\001\008\000\008\001\009\001\002\001\038\000\
\017\001\040\000\015\001\019\001\017\000\018\001\016\001\020\001\
\023\001\022\001\002\001\024\001\006\001\007\001\008\001\009\001\
\042\000\043\000\001\001\002\001\003\001\004\001\005\001\002\001\
\007\001\025\001\010\001\026\001\054\000\010\001\056\000\021\001\
\015\001\010\001\060\000\021\001\062\000\063\000\010\001\065\000\
\255\255\021\001\068\000\006\001\007\001\008\001\009\001\010\001\
\011\001\012\001\013\001\014\001\255\255\016\001\017\001\255\255\
\255\255\255\255\021\001\255\255\006\001\007\001\025\001\026\001\
\010\001\011\001\012\001\013\001\014\001\255\255\016\001\017\001\
\255\255\255\255\255\255\021\001\255\255\006\001\007\001\025\001\
\026\001\010\001\011\001\012\001\013\001\014\001\255\255\016\001\
\017\001\255\255\255\255\255\255\021\001\255\255\255\255\255\255\
\025\001\026\001\010\001\011\001\012\001\013\001\014\001\255\255\
\016\001\017\001\255\255\255\255\255\255\021\001\255\255\255\255\
\255\255\025\001\026\001\010\001\011\001\012\001\013\001\014\001\
\255\255\016\001\017\001\255\255\255\255\255\255\021\001\255\255\
\255\255\255\255\025\001\026\001\010\001\011\001\012\001\013\001\
\014\001\255\255\016\001\017\001\255\255\255\255\255\255\021\001\
\255\255\255\255\255\255\025\001\026\001\010\001\011\001\012\001\
\013\001\014\001\255\255\016\001\017\001\255\255\255\255\255\255\
\021\001\255\255\255\255\255\255\025\001\026\001\010\001\011\001\
\012\001\013\001\014\001\255\255\016\001\017\001\255\255\255\255\
\255\255\021\001\255\255\255\255\255\255\025\001\026\001\001\001\
\002\001\003\001\004\001\005\001\255\255\016\001\017\001\255\255\
\255\255\255\255\021\001\255\255\255\255\015\001\025\001\026\001\
\006\001\007\001\008\001\009\001\010\001\011\001\012\001\013\001\
\014\001\027\000\028\000\029\000\030\000\031\000\032\000\033\000\
\034\000\035\000"

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
  LETREC\000\
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
# 27 "pcfparse.mly"
                    ( _1 )
# 227 "pcfparse.ml"
               : Pcfast.expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 5 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'seqident) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 31 "pcfparse.mly"
                                              ( Letrec(_2, (body _3 _5), _7) )
# 237 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 5 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 4 : 'seqident) in
    let _6 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _8 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 32 "pcfparse.mly"
                                              ( Letrec(_3, (body _4 _6), _8) )
# 247 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 5 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'seqident) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 33 "pcfparse.mly"
                                              ( Let(_2, (body _3 _5) , _7) )
# 257 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 2 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 34 "pcfparse.mly"
                                              ( Fun(_2, _4) )
# 265 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 35 "pcfparse.mly"
                                              ( If(_2, _4, _6) )
# 274 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 36 "pcfparse.mly"
                                              ( _1 )
# 281 "pcfparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'application) in
    Obj.repr(
# 40 "pcfparse.mly"
                                     ( _1 )
# 288 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 41 "pcfparse.mly"
                                     ( Binop("=", _1, _3) )
# 296 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 42 "pcfparse.mly"
                                     ( Binop(">", _1, _3) )
# 304 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 43 "pcfparse.mly"
                                     ( Binop(">=", _1, _3) )
# 312 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 44 "pcfparse.mly"
                                     ( Binop("<", _1, _3) )
# 320 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 45 "pcfparse.mly"
                                     ( Binop("<=", _1, _3) )
# 328 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 46 "pcfparse.mly"
                                     ( Binop("+", _1, _3) )
# 336 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 47 "pcfparse.mly"
                                     ( Binop("-", _1, _3) )
# 344 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 48 "pcfparse.mly"
                                     ( Binop("*", _1, _3) )
# 352 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 49 "pcfparse.mly"
                                     ( Binop("/", _1, _3) )
# 360 "pcfparse.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'atom) in
    Obj.repr(
# 61 "pcfparse.mly"
                   ( _1 )
# 367 "pcfparse.ml"
               : 'application))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'atom) in
    Obj.repr(
# 62 "pcfparse.mly"
                   ( Monop("-", _2) )
# 374 "pcfparse.ml"
               : 'application))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'application) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'atom) in
    Obj.repr(
# 63 "pcfparse.mly"
                   ( App(_1, _2) )
# 382 "pcfparse.ml"
               : 'application))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 67 "pcfparse.mly"
                 ( Int(_1) )
# 389 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    Obj.repr(
# 68 "pcfparse.mly"
                 ( Bool(true) )
# 395 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    Obj.repr(
# 69 "pcfparse.mly"
                 ( Bool(false) )
# 401 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 70 "pcfparse.mly"
                 ( String(_1) )
# 408 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 71 "pcfparse.mly"
                 ( Ident(_1) )
# 415 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 72 "pcfparse.mly"
                 ( _2 )
# 422 "pcfparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : string) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'seqident) in
    Obj.repr(
# 76 "pcfparse.mly"
                  ( _1 :: _2 )
# 430 "pcfparse.ml"
               : 'seqident))
; (fun __caml_parser_env ->
    Obj.repr(
# 77 "pcfparse.mly"
                  ( [ ] )
# 436 "pcfparse.ml"
               : 'seqident))
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
