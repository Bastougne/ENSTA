type token =
  | EOF
  | INT of (int)
  | IDENT of (string)
  | TRUE
  | FALSE
  | STRING of (string)
  | COLONEQUAL
  | WHILE
  | DO
  | DONE
  | BEGIN
  | END
  | RETURN
  | VAR
  | PLUS
  | MINUS
  | MULT
  | DIV
  | EQUALEQUAL
  | GREATER
  | SMALLER
  | GREATEREQUAL
  | SMALLEREQUAL
  | LPAR
  | RPAR
  | SEMICOLON
  | COMMA
  | LBRACKET
  | RBRACKET
  | IF
  | THEN
  | ELSE
  | ENDIF
  | PRINT

open Parsing;;
let _ = parse_error;;
# 2 "impparse.mly"
open Impast ;;
# 42 "impparse.ml"
let yytransl_const = [|
    0 (* EOF *);
  259 (* TRUE *);
  260 (* FALSE *);
  262 (* COLONEQUAL *);
  263 (* WHILE *);
  264 (* DO *);
  265 (* DONE *);
  266 (* BEGIN *);
  267 (* END *);
  268 (* RETURN *);
  269 (* VAR *);
  270 (* PLUS *);
  271 (* MINUS *);
  272 (* MULT *);
  273 (* DIV *);
  274 (* EQUALEQUAL *);
  275 (* GREATER *);
  276 (* SMALLER *);
  277 (* GREATEREQUAL *);
  278 (* SMALLEREQUAL *);
  279 (* LPAR *);
  280 (* RPAR *);
  281 (* SEMICOLON *);
  282 (* COMMA *);
  283 (* LBRACKET *);
  284 (* RBRACKET *);
  285 (* IF *);
  286 (* THEN *);
  287 (* ELSE *);
  288 (* ENDIF *);
  289 (* PRINT *);
    0|]

let yytransl_block = [|
  257 (* INT *);
  258 (* IDENT *);
  261 (* STRING *);
    0|]

let yylhs = "\255\255\
\001\000\001\000\002\000\002\000\003\000\003\000\006\000\006\000\
\004\000\007\000\007\000\009\000\009\000\008\000\008\000\010\000\
\010\000\010\000\010\000\010\000\010\000\010\000\010\000\005\000\
\005\000\005\000\005\000\005\000\005\000\005\000\005\000\005\000\
\005\000\005\000\005\000\005\000\005\000\011\000\011\000\012\000\
\012\000\014\000\014\000\013\000\013\000\013\000\013\000\013\000\
\000\000"

let yylen = "\002\000\
\001\000\002\000\001\000\001\000\003\000\006\000\000\000\002\000\
\008\000\000\000\002\000\000\000\003\000\001\000\002\000\007\000\
\005\000\004\000\007\000\003\000\003\000\005\000\005\000\004\000\
\003\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\002\000\003\000\001\000\004\000\000\000\001\000\000\000\
\002\000\000\000\003\000\001\000\001\000\001\000\001\000\001\000\
\002\000"

let yydefred = "\000\000\
\000\000\000\000\001\000\000\000\000\000\049\000\000\000\003\000\
\004\000\000\000\000\000\002\000\000\000\000\000\005\000\000\000\
\000\000\011\000\000\000\044\000\000\000\045\000\046\000\047\000\
\000\000\000\000\000\000\036\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\013\000\000\000\000\000\000\000\
\000\000\000\000\035\000\000\000\000\000\032\000\033\000\000\000\
\000\000\000\000\000\000\000\000\006\000\008\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\041\000\
\024\000\037\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\009\000\015\000\000\000\000\000\000\000\
\000\000\000\000\020\000\021\000\000\000\000\000\043\000\018\000\
\000\000\000\000\000\000\000\000\000\000\022\000\000\000\017\000\
\000\000\023\000\000\000\000\000\019\000\016\000"

let yydgoto = "\002\000\
\006\000\007\000\008\000\009\000\048\000\047\000\014\000\069\000\
\018\000\070\000\081\000\049\000\028\000\072\000"

let yysindex = "\004\000\
\001\000\000\000\000\000\247\254\031\255\000\000\001\000\000\000\
\000\000\035\255\015\255\000\000\019\255\023\255\000\000\218\255\
\047\255\000\000\044\255\000\000\235\254\000\000\000\000\000\000\
\218\255\218\255\228\255\000\000\019\255\045\255\218\255\218\255\
\040\255\066\000\218\255\218\255\218\255\218\255\218\255\218\255\
\218\255\218\255\218\255\039\255\000\000\045\255\005\255\029\000\
\036\255\246\255\000\000\040\255\040\255\000\000\000\000\220\255\
\220\255\220\255\220\255\220\255\000\000\000\000\012\255\218\255\
\005\255\218\255\218\255\042\255\055\255\005\255\218\255\000\000\
\000\000\000\000\218\255\218\255\218\255\005\000\066\255\077\000\
\056\255\210\255\218\255\000\000\000\000\029\000\042\000\061\255\
\014\000\005\255\000\000\000\000\005\255\062\255\000\000\000\000\
\063\255\085\255\083\255\067\255\079\255\000\000\218\255\000\000\
\005\255\000\000\054\000\074\255\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\086\255\000\000\000\000\087\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\054\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\087\255\034\255\093\255\000\000\
\075\255\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\034\255\000\000\099\255\
\000\000\000\000\000\000\094\255\113\255\000\000\000\000\128\255\
\143\255\158\255\173\255\188\255\000\000\000\000\000\000\000\000\
\000\000\082\255\000\000\000\000\000\000\021\255\000\000\000\000\
\000\000\000\000\000\000\093\255\000\000\000\000\000\000\100\255\
\000\000\000\000\093\255\000\000\000\000\099\255\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000"

let yygindex = "\000\000\
\119\000\000\000\239\255\000\000\240\255\083\000\000\000\194\255\
\101\000\000\000\000\000\184\255\000\000\056\000"

let yytablesize = 355
let yytable = "\027\000\
\003\000\031\000\079\000\088\000\001\000\032\000\063\000\085\000\
\033\000\034\000\094\000\064\000\046\000\010\000\065\000\050\000\
\066\000\075\000\052\000\053\000\054\000\055\000\056\000\057\000\
\058\000\059\000\060\000\099\000\046\000\014\000\100\000\014\000\
\011\000\067\000\076\000\007\000\013\000\068\000\077\000\015\000\
\007\000\016\000\108\000\007\000\017\000\007\000\019\000\078\000\
\029\000\080\000\082\000\014\000\014\000\030\000\086\000\037\000\
\038\000\005\000\087\000\073\000\089\000\048\000\007\000\061\000\
\083\000\084\000\007\000\048\000\048\000\048\000\048\000\048\000\
\048\000\048\000\048\000\048\000\091\000\048\000\048\000\048\000\
\092\000\048\000\034\000\048\000\097\000\101\000\107\000\102\000\
\034\000\034\000\103\000\104\000\034\000\034\000\034\000\034\000\
\034\000\105\000\034\000\034\000\034\000\030\000\034\000\106\000\
\034\000\110\000\038\000\030\000\030\000\010\000\012\000\030\000\
\030\000\030\000\030\000\030\000\040\000\030\000\030\000\030\000\
\031\000\030\000\042\000\030\000\039\000\012\000\031\000\031\000\
\062\000\045\000\031\000\031\000\031\000\031\000\031\000\025\000\
\031\000\031\000\031\000\000\000\031\000\095\000\031\000\000\000\
\000\000\025\000\025\000\025\000\025\000\025\000\026\000\025\000\
\025\000\025\000\000\000\025\000\000\000\025\000\000\000\000\000\
\026\000\026\000\026\000\026\000\026\000\028\000\026\000\026\000\
\026\000\000\000\026\000\000\000\026\000\000\000\000\000\028\000\
\028\000\028\000\028\000\028\000\027\000\028\000\028\000\028\000\
\000\000\028\000\000\000\028\000\000\000\000\000\027\000\027\000\
\027\000\027\000\027\000\029\000\027\000\027\000\027\000\000\000\
\027\000\000\000\027\000\000\000\000\000\029\000\029\000\029\000\
\029\000\029\000\000\000\029\000\029\000\029\000\000\000\029\000\
\000\000\029\000\020\000\021\000\022\000\023\000\024\000\035\000\
\036\000\037\000\038\000\039\000\040\000\041\000\042\000\043\000\
\025\000\035\000\036\000\037\000\038\000\000\000\000\000\093\000\
\026\000\035\000\036\000\037\000\038\000\039\000\040\000\041\000\
\042\000\043\000\000\000\000\000\000\000\000\000\000\000\044\000\
\000\000\000\000\004\000\035\000\036\000\037\000\038\000\039\000\
\040\000\041\000\042\000\043\000\090\000\005\000\000\000\000\000\
\000\000\074\000\035\000\036\000\037\000\038\000\039\000\040\000\
\041\000\042\000\043\000\035\000\036\000\037\000\038\000\039\000\
\040\000\041\000\042\000\043\000\000\000\000\000\000\000\000\000\
\000\000\098\000\035\000\036\000\037\000\038\000\039\000\040\000\
\041\000\042\000\043\000\000\000\000\000\000\000\071\000\035\000\
\036\000\037\000\038\000\039\000\040\000\041\000\042\000\043\000\
\000\000\000\000\096\000\035\000\036\000\037\000\038\000\039\000\
\040\000\041\000\042\000\043\000\000\000\000\000\109\000\035\000\
\036\000\037\000\038\000\039\000\040\000\041\000\042\000\043\000\
\000\000\051\000\035\000\036\000\037\000\038\000\039\000\040\000\
\041\000\042\000\043\000"

let yycheck = "\016\000\
\000\000\023\001\065\000\076\000\001\000\027\001\002\001\070\000\
\025\000\026\000\083\000\007\001\030\000\023\001\010\001\032\000\
\012\001\006\001\035\000\036\000\037\000\038\000\039\000\040\000\
\041\000\042\000\043\000\090\000\046\000\009\001\093\000\011\001\
\002\001\029\001\023\001\002\001\002\001\033\001\027\001\025\001\
\007\001\027\001\105\000\010\001\026\001\012\001\024\001\064\000\
\002\001\066\000\067\000\031\001\032\001\010\001\071\000\016\001\
\017\001\013\001\075\000\024\001\077\000\008\001\029\001\025\001\
\023\001\011\001\033\001\014\001\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\011\001\024\001\025\001\026\001\
\025\001\028\001\008\001\030\001\024\001\024\001\103\000\025\001\
\014\001\015\001\006\001\009\001\018\001\019\001\020\001\021\001\
\022\001\031\001\024\001\025\001\026\001\008\001\028\001\025\001\
\030\001\032\001\025\001\014\001\015\001\024\001\024\001\018\001\
\019\001\020\001\021\001\022\001\024\001\024\001\025\001\026\001\
\008\001\028\001\024\001\030\001\025\001\007\000\014\001\015\001\
\046\000\029\000\018\001\019\001\020\001\021\001\022\001\008\001\
\024\001\025\001\026\001\255\255\028\001\086\000\030\001\255\255\
\255\255\018\001\019\001\020\001\021\001\022\001\008\001\024\001\
\025\001\026\001\255\255\028\001\255\255\030\001\255\255\255\255\
\018\001\019\001\020\001\021\001\022\001\008\001\024\001\025\001\
\026\001\255\255\028\001\255\255\030\001\255\255\255\255\018\001\
\019\001\020\001\021\001\022\001\008\001\024\001\025\001\026\001\
\255\255\028\001\255\255\030\001\255\255\255\255\018\001\019\001\
\020\001\021\001\022\001\008\001\024\001\025\001\026\001\255\255\
\028\001\255\255\030\001\255\255\255\255\018\001\019\001\020\001\
\021\001\022\001\255\255\024\001\025\001\026\001\255\255\028\001\
\255\255\030\001\001\001\002\001\003\001\004\001\005\001\014\001\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\015\001\014\001\015\001\016\001\017\001\255\255\255\255\030\001\
\023\001\014\001\015\001\016\001\017\001\018\001\019\001\020\001\
\021\001\022\001\255\255\255\255\255\255\255\255\255\255\028\001\
\255\255\255\255\002\001\014\001\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\008\001\013\001\255\255\255\255\
\255\255\028\001\014\001\015\001\016\001\017\001\018\001\019\001\
\020\001\021\001\022\001\014\001\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\255\255\255\255\255\255\255\255\
\255\255\028\001\014\001\015\001\016\001\017\001\018\001\019\001\
\020\001\021\001\022\001\255\255\255\255\255\255\026\001\014\001\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\255\255\255\255\025\001\014\001\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\255\255\255\255\025\001\014\001\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\255\255\024\001\014\001\015\001\016\001\017\001\018\001\019\001\
\020\001\021\001\022\001"

let yynames_const = "\
  EOF\000\
  TRUE\000\
  FALSE\000\
  COLONEQUAL\000\
  WHILE\000\
  DO\000\
  DONE\000\
  BEGIN\000\
  END\000\
  RETURN\000\
  VAR\000\
  PLUS\000\
  MINUS\000\
  MULT\000\
  DIV\000\
  EQUALEQUAL\000\
  GREATER\000\
  SMALLER\000\
  GREATEREQUAL\000\
  SMALLEREQUAL\000\
  LPAR\000\
  RPAR\000\
  SEMICOLON\000\
  COMMA\000\
  LBRACKET\000\
  RBRACKET\000\
  IF\000\
  THEN\000\
  ELSE\000\
  ENDIF\000\
  PRINT\000\
  "

let yynames_block = "\
  INT\000\
  IDENT\000\
  STRING\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    Obj.repr(
# 26 "impparse.mly"
      ( [] )
# 298 "impparse.ml"
               : Impast.program))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'toplevel) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Impast.program) in
    Obj.repr(
# 27 "impparse.mly"
                   ( _1 :: _2 )
# 306 "impparse.ml"
               : Impast.program))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'var_decl) in
    Obj.repr(
# 31 "impparse.mly"
           ( Vardecl _1 )
# 313 "impparse.ml"
               : 'toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'fun_def) in
    Obj.repr(
# 32 "impparse.mly"
          ( Fundef _1 )
# 320 "impparse.ml"
               : 'toplevel))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string) in
    Obj.repr(
# 36 "impparse.mly"
                      ( (_2, Scalar) )
# 327 "impparse.ml"
               : 'var_decl))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    Obj.repr(
# 37 "impparse.mly"
                                             ( (_2, (Array _4)) )
# 335 "impparse.ml"
               : 'var_decl))
; (fun __caml_parser_env ->
    Obj.repr(
# 41 "impparse.mly"
  ( [] )
# 341 "impparse.ml"
               : 'opt_var_decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'var_decl) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'opt_var_decls) in
    Obj.repr(
# 42 "impparse.mly"
                         ( _1 :: _2 )
# 349 "impparse.ml"
               : 'opt_var_decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 7 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 5 : 'opt_params) in
    let _6 = (Parsing.peek_val __caml_parser_env 2 : 'opt_var_decls) in
    let _7 = (Parsing.peek_val __caml_parser_env 1 : 'instrs) in
    Obj.repr(
# 47 "impparse.mly"
    ( { f_name = _1 ; params = _3 ; vars = _6 ; body = _7 } )
# 359 "impparse.ml"
               : 'fun_def))
; (fun __caml_parser_env ->
    Obj.repr(
# 51 "impparse.mly"
  ( [] )
# 365 "impparse.ml"
               : 'opt_params))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : string) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'params) in
    Obj.repr(
# 52 "impparse.mly"
               ( _1 :: _2 )
# 373 "impparse.ml"
               : 'opt_params))
; (fun __caml_parser_env ->
    Obj.repr(
# 56 "impparse.mly"
  ( [] )
# 379 "impparse.ml"
               : 'params))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'params) in
    Obj.repr(
# 57 "impparse.mly"
                     ( _2 :: _3 )
# 387 "impparse.ml"
               : 'params))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'instr) in
    Obj.repr(
# 61 "impparse.mly"
        ( _1 )
# 394 "impparse.ml"
               : 'instrs))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'instr) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'instrs) in
    Obj.repr(
# 62 "impparse.mly"
               ( Seq (_1, _2) )
# 402 "impparse.ml"
               : 'instrs))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 5 : 'expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : 'instrs) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'instrs) in
    Obj.repr(
# 67 "impparse.mly"
    ( If (_2, _4, _6) )
# 411 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 3 : 'expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'instrs) in
    Obj.repr(
# 69 "impparse.mly"
    ( While (_2, _4) )
# 419 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 71 "impparse.mly"
    ( Assign (_1, _3) )
# 427 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'expr) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 73 "impparse.mly"
    ( ArrayWrite (_1, _3, _6) )
# 436 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'instrs) in
    Obj.repr(
# 75 "impparse.mly"
    ( _2 )
# 443 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'opt_expr) in
    Obj.repr(
# 77 "impparse.mly"
    ( Return _2 )
# 450 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'opt_exprs) in
    Obj.repr(
# 79 "impparse.mly"
    ( Iapp (_1, _3) )
# 458 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'opt_exprs) in
    Obj.repr(
# 81 "impparse.mly"
    ( Print _3 )
# 465 "impparse.ml"
               : 'instr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'opt_exprs) in
    Obj.repr(
# 85 "impparse.mly"
                                 ( App (_1, _3) )
# 473 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 86 "impparse.mly"
                                 ( Binop ("==", _1, _3) )
# 481 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 87 "impparse.mly"
                                 ( Binop (">", _1, _3) )
# 489 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 88 "impparse.mly"
                                 ( Binop (">=", _1, _3) )
# 497 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 89 "impparse.mly"
                                 ( Binop ("<", _1, _3) )
# 505 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 90 "impparse.mly"
                                 ( Binop ("<=", _1, _3) )
# 513 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 91 "impparse.mly"
                                 ( Binop ("+", _1, _3) )
# 521 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 92 "impparse.mly"
                                 ( Binop ("-", _1, _3) )
# 529 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 93 "impparse.mly"
                                 ( Binop ("*", _1, _3) )
# 537 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 94 "impparse.mly"
                                 ( Binop ("/", _1, _3) )
# 545 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 95 "impparse.mly"
                                 ( Monop ("-", _2) )
# 552 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 96 "impparse.mly"
                                 ( _2 )
# 559 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'atom) in
    Obj.repr(
# 97 "impparse.mly"
                                 ( _1 )
# 566 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 98 "impparse.mly"
                                 ( ArrayRead (_1, _3) )
# 574 "impparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    Obj.repr(
# 102 "impparse.mly"
  ( None )
# 580 "impparse.ml"
               : 'opt_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 103 "impparse.mly"
                     ( Some _1 )
# 587 "impparse.ml"
               : 'opt_expr))
; (fun __caml_parser_env ->
    Obj.repr(
# 107 "impparse.mly"
  ( [] )
# 593 "impparse.ml"
               : 'opt_exprs))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'exprs) in
    Obj.repr(
# 108 "impparse.mly"
                           ( _1 :: _2 )
# 601 "impparse.ml"
               : 'opt_exprs))
; (fun __caml_parser_env ->
    Obj.repr(
# 112 "impparse.mly"
  ( [] )
# 607 "impparse.ml"
               : 'exprs))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exprs) in
    Obj.repr(
# 113 "impparse.mly"
                           ( _2 :: _3 )
# 615 "impparse.ml"
               : 'exprs))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 117 "impparse.mly"
                 ( Int (_1) )
# 622 "impparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    Obj.repr(
# 118 "impparse.mly"
                 ( Bool (true) )
# 628 "impparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    Obj.repr(
# 119 "impparse.mly"
                 ( Bool (false) )
# 634 "impparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 120 "impparse.mly"
                 ( String (_1) )
# 641 "impparse.ml"
               : 'atom))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 121 "impparse.mly"
                 ( Ident (_1) )
# 648 "impparse.ml"
               : 'atom))
(* Entry program *)
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
let program (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Impast.program)
