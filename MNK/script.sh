#!/bin/bash
g++ -O mnk.cpp -o rez -L/usr/local/lib64 -llapack -lblas  -lm
./rez
