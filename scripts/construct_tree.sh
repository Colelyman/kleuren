#!/bin/bash

# This script will construct the tree using IQ-TREE from 
# the supermatrix.
# If you have not already constructed the supermatrix, run
# `python scripts/bubble_to_msa.py` for instructions.
#
# There is exactly one input parameter, the path to the supermatrix.

# unzip the file if the directory does not exist
[ ! -d ../thirdparty/iqtree-omp-1.5.5-Linux/ ] && tar zxcvf ../thirdparty/iqtree-omp-1.5.5-Linux.tar.gz

# If you have IQ-TREE install elsewhere, change the path below
IQ_TREE=../thirdparty/iqtree-omp-1.5.5-Linux/bin/iqtree-omp
# If you know what you are doing, feel free to change MODEL.
# TEST will automatically fit the best one.
MODEL="TEST"
CORES=4

$IQ_TREE -s $1 -m $MODEL -nt $CORES
