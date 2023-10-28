orig:=$(wildcard problem_*/*.txt)
ode45:=$(patsubst %.txt, %.ode45.dat, $(orig))
ode23:=$(patsubst %.txt, %.ode23.dat, $(orig))
ode113:=$(patsubst %.txt, %.ode113.dat, $(orig))
ode15s:=$(patsubst %.txt, %.ode15s.dat, $(orig))
ode23s:=$(patsubst %.txt, %.ode23s.dat, $(orig))
ode23t:=$(patsubst %.txt, %.ode23t.dat, $(orig))
ode23tb:=$(patsubst %.txt, %.ode23tb.dat, $(orig))

data=ode45.txt ode23.txt ode113.txt ode15s.txt ode23s.txt ode23t.txt ode23tb.txt

all: pdf

%.ode45.dat : %.txt
	grep "ode45" $< | cut -d',' -f 4 > $@

%.ode23.dat : %.txt
	grep "ode23," $< | cut -d',' -f 4 > $@

%.ode113.dat: %.txt
	grep "ode113" $< | cut -d',' -f 4 >> $@

%.ode15s.dat: %.txt
	grep "ode15s" $< | cut -d',' -f 4 >> $@

%.ode23s.dat : %.txt
	grep "ode23s" $< | cut -d',' -f 4 > $@

%.ode23t.dat : %.txt
	grep "ode23t," $< | cut -d',' -f 4 > $@

%.ode23tb.dat : %.txt
	grep "ode23tb" $< | cut -d',' -f 4 > $@

ode45.txt: $(ode45)
	@cat $^ > $@

ode23.txt: $(ode23)
	@cat $^ > $@

ode113.txt: $(ode113)
	@cat $^ > $@

ode15s.txt: $(ode15s)
	@cat $^ > $@

ode23s.txt: $(ode23s)
	@cat $^ > $@

ode23t.txt: $(ode23t)
	@cat $^ > $@

ode23tb.txt: $(ode23tb)
	@cat $^ > $@

pdf: $(data)
	 gnuplot config.gnuplot

clean:
	@rm -f $(ode45) $(ode23) $(ode113) $(ode15s) $(ode23s) $(ode23t) $(ode23tb)
	@rm -f ode45.txt ode23.txt ode113.txt ode15s.txt ode23s.txt ode23t.txt ode23tb.txt

realclean: clean
	@rm -f out.pdf
