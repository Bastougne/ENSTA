OCAMLCOMPILE = ocamlc

OBJS = pcflex.cmo pcfast.cmo pcfparse.cmo pcfsem.cmo pcfloop.cmo

INTFS = pcfparse.cmi

pcfloop: $(OBJS)
	$(OCAMLCOMPILE) -o $@ $(OBJS)

uninstall:
	cp -b  pcfsem.ml pcfsem-eleves.ml
	cp -b pcfsem-corrige.ml pcfsem.ml
	chmod a+r pcfsem.ml

install:
	cp -b pcfsem.ml pcfsem-corrige.ml
	chmod og-rwx pcfsem-corrige.ml
	cp -b pcfsem-eleves.ml pcfsem.ml
	chmod a+r pcfsem-eleves.ml

pcfloop.cmo: pcfast.cmi  pcfsem.cmi pcfparse.cmi pcflex.cmi

pcfsem.cmi: pcfast.cmi pcfsem.cmo

pcfsem.cmo: pcfast.cmi

pcflex.cmo: pcfparse.cmi

pcfparse.cmi: pcfast.cmi

pcfparse.cmo: pcfast.cmi

pcfparse.mli: pcfparse.ml

pcflex.ml: pcflex.mll
	ocamllex $<

pcfparse.ml: pcfparse.mly
	ocamlyacc $<

pcfast.cmi: pcfast.cmo

pcflex.cmi: pcflex.cmo

clean:
	/bin/rm -f *.cmo *.cmi pcfparse.ml pcfparse.mli pcflex.ml pcfloop *~



.ml.cmo:
	$(OCAMLCOMPILE) -c $<

.mli.cmi:
	$(OCAMLCOMPILE) -c $<

.SUFFIXES:

.SUFFIXES: .ml .mli .mly .mll .cmo .cmi

tarball-enonce:
	tar cvzhf tarball-enonce.tgz \
		Makefile pcflex.mll fact.pcf pcfloop.ml pcfast.ml pcfparse.mly pcfsem-eleves.ml

tarball-solution:
	tar cvzhf tarball-solution.tgz \
		Makefile pcflex.mll fact.pcf pcfloop.ml pcfast.ml pcfparse.mly pcfsem.ml
