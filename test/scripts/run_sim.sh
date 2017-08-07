#!/bin/bash

# this script will reproduce the results found in the paper

COLORS=../data/sim_population/sim_population.colors.txt
KMERS=../data/sim_population/sim_population.count.txt
BUBBLES=sim_population.bubbles.out
MATRIX=sim_population.matrix.out

MIN_COLORS=16

../../kleuren -c $COLORS -b $BUBBLES -k $KMERS -m $MATRIX -n $MIN_COLORS
