reset

set title "Time to calculate fib(x)"
set ylabel "time(ns)"
set xlabel "nth fibnocci number"

plot "output.txt" using 2 with line lw 3 title "user space", \
'' using 3 with line lw 3 title "kernel space"
