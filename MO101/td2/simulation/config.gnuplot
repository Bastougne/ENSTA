set terminal pdf color
set output 'out.pdf'
set logscale y
set title "number of evaluation of 'f' for each problem and each numerical integraiton method"
plot 'ode45.txt' u 1 w l, 'ode23.txt' u 1 w l, 'ode113.txt' u 1 w l, \
     'ode15s.txt' u 1 w l, \
     'ode23s.txt' u 1 w l, \
     'ode23t.txt' u 1 w l, \
     'ode23tb.txt' u 1 w l