let line = '\n'
let space = [' ' '\t' '\n']

rule count nbchars nbwords nblines = parse
| eof   { ( nbchars, nbwords, nblines ) }
| line  { count ( nbchars + 1 ) nbwords ( nblines + 1 ) lexbuf }
| space { count ( nbchars + 1 ) nbwords nblines lexbuf }
| _     { inword ( nbchars + 1 ) ( nbwords + 1 ) nblines lexbuf }

and inword nbchars nbwords nblines = parse
| eof   { ( nbchars, nbwords, nblines ) }
| line  { count ( nbchars + 1 ) nbwords ( nblines + 1 ) lexbuf }
| space { count ( nbchars + 1 ) nbwords nblines lexbuf }
| _     { inword ( nbchars + 1 ) nbwords nblines lexbuf }
