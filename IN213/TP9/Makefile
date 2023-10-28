# Where to find the compiler... With a trailing / !
BINDIR=
CAMLC=$(BINDIR)ocamlc
CAMLDEP=$(BINDIR)ocamldep
CAMLLEX=$(BINDIR)ocamllex
CAMLYACC=$(BINDIR)ocamlyacc
#COMPFLAGS=-w A-4-6-9 -warn-error A -g
COMPFLAGS=

# User definitions must be here

COMMON_SRCS = printByteCode.ml
COMMON_GENERATED =
COMMON_MLIS = vmBytecode.mli printByteCode.mli
COMMON_OBJS = $(COMMON_SRCS:.ml=.cmo)

COMP_EXEC = pcfc
COMP_SRCS = pcfast.ml compile.ml mainCompile.ml
COMP_GENERATED = pcflex.ml pcfparse.ml
COMP_MLIS = compile.mli
COMP_OBJS = $(COMP_GENERATED:.ml=.cmo) $(COMP_SRCS:.ml=.cmo)

VM_EXEC = pcfrun
VM_SRCS = vmExec.ml mainRun.ml
VM_GENERATED =
VM_MLIS = vmExec.mli
VM_OBJS = $(VM_GENERATED:.ml=.cmo) $(VM_SRCS:.ml=.cmo)


# Building the world
all: $(COMP_EXEC) $(VM_EXEC)

$(COMP_EXEC): $(COMMON_OBJS) $(COMP_OBJS)
	$(CAMLC) $(COMPFLAGS) -cclib -lunix $(COMMON_OBJS) $(COMP_OBJS) -o $(COMP_EXEC)

$(VM_EXEC): $(COMMON_OBJS) $(VM_OBJS)
	$(CAMLC) $(COMPFLAGS) -cclib -lunix $(COMMON_OBJS) $(VM_OBJS) -o $(VM_EXEC)




.SUFFIXES:
.SUFFIXES: .ml .mli .cmo .cmi .cmx
.SUFFIXES: .mll .mly

.ml.cmo:
	$(CAMLC) $(COMPFLAGS) -c $<

.mli.cmi:
	$(CAMLC) $(COMPFLAGS) -c $<

.mll.ml:
	$(CAMLLEX) $<

.mly.ml:
	$(CAMLYACC) $<

# Clean up
clean:
	rm -f *.cm[io] *.cmx *~ .*~ *.o a.out
	rm -f pcfparse.mli
	rm -f $(COMMON_OBJS) $(COMP_OBJS) $(VM_OBJS)
	rm -f $(COMP_EXEC) $(VM_EXEC)
	rm -f $(COMMON_GENERATED) $(COMP_GENERATED) $(VM_GENERATED)

# Dependencies
depend: $(COMMON_MLI) $(COMP_MLIS) $(VM_MLIS) $(COMP_GENERATED) pcfparse.mli $(COMMON_GENERATED) $(VM_GENERATED) $(COMMON_SRCS) $(COMP_SRCS) $(VM_SRCS)
	$(CAMLDEP) $(COMMON_MLI) $(COMP_MLIS) $(VM_MLIS) $(COMP_GENERATED) pcfparse.mli $(COMMON_GENERATED) $(VM_GENERATED) $(COMMON_SRCS) $(COMP_SRCS) $(VM_SRCS) > .depend

include .depend

tarball-enonce:
	rm -f tarball-enonce.tgz
	tar cvzhf tarball-enonce.tgz \
		../std.pdf Makefile pcfast.ml vmBytecode.mli pcflex.mll pcfparse.mly \
		compile.mli printByteCode.ml vmExec.mli mainCompile.ml printByteCode.mli \
		mainRun.ml test.pcf compile-eleves.ml vmExec-eleves.ml

tarball-solution:
	rm -f tarball-solution.tgz
	tar cvzhf tarball-solution.tgz \
		../ctd.pdf Makefile pcfast.ml vmBytecode.mli pcflex.mll pcfparse.mly vmExec.ml \
		compile.mli printByteCode.ml vmExec.mli mainCompile.ml printByteCode.mli \
		mainRun.ml test.pcf compile.ml vmExec.ml
