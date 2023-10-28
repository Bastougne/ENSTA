# Compilateurs
OCC = ocamlc
OCL = ocamllex
OCY = ocamlyacc

# Fichiers compilés, à produire pour fabriquer l'exécutable
OBJS = pcflex.cmo pcfast.cmo pcfparse.cmo pcfsem.cmo pcfloop.cmo

pcfloop: $(OBJS)
	$(OCC) -o $@ $(OBJS)

# Les cibles auxiliaires
# (note: une cible avec  « :: » peut être étendue par la suite)
clean::
	/bin/rm -f *~ *.cmo *.cmo *.o *.cmi *.cmt *.cmti \
                   pcfparse.ml pcfparse.mli pcflex.ml pcfloop

# Les dépendances
pcfloop.cmo: pcfast.cmi pcfparse.cmi pcflex.cmi

pcflex.cmo: pcfparse.cmi

pcfparse.cmi: pcfast.cmi

pcfparse.cmo: pcfast.cmi

pcfsem.cmo: pcfast.cmi

pcfparse.mli: pcfparse.ml

pcfast.cmi: pcfast.cmo

pcflex.cmi: pcflex.cmo

# Générations de fichiers compilés selon leurs extensions (suffixes) :
# .ext1.ext2 : comment passer de foo.ext1 à foo.ext2
.ml.cmo:
	$(OCC) -c $<

.mli.cmi:
	$(OCC) -c $<

.mll.ml:
	$(OCL) $<

.mly.ml:
	$(OCY) $<

# Déclaration de suffixes :
#  - d'abord, on supprime les suffixes connus de make (.c, .o, etc.)
.SUFFIXES:

# - ensuite, on déclare nos suffixes
.SUFFIXES: .ml .mli .mly .mll .cmo .cmi

tarball-enonce:
	tar cvzhf tarball-enonce.tgz \
		../std.pdf Makefile pcfast.ml pcfparse.mly fact.pcf pcflex.mll pcfloop.ml pcfsem-eleves.ml

tarball-solution:
	tar cvzhf tarball-solution.tgz \
		../ctd.pdf Makefile pcfast.ml pcfparse.mly fact.pcf pcflex.mll pcfloop.ml pcfsem.ml
