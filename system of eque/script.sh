#!/bin/bash
rm def.h
COUNTER=10
         while [ $COUNTER -lt 60000 ]; do

               echo "#define size $COUNTER" >>def.h
	       gcc -o res linesys.c -lm /usr/lib/lapack/liblapack.so.3
	        ./res>>norma.txt 
		rm def.h
	      echo "  $COUNTER">>norma.txt

             let COUNTER=$((COUNTER*2))
         done
gnuplot << EOP
set terminal jpeg size 640,480
set output "norma.jpg"
set title "NOrma"
set xlabel "Size of the matrix(N) "
set logscale y
set ylabel "Time LAPACK"
plot "norma.txt" with lines

EOP


