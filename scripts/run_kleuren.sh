#!/bin/bash

#SBATCH --time=96:00:00   # walltime
#SBATCH --ntasks=1   # number of processor cores (i.e. tasks)
#SBATCH --nodes=1   # number of nodes
#SBATCH --mem-per-cpu=8G   # memory per CPU core

# This script is an example script used to run kleuren on a SLURM system.
# This can be run as a normal bash script if not on a SLURM system.

# Compatibility variables for PBS. Delete if not needed.
export PBS_NODEFILE=`/fslapps/fslutils/generate_pbs_nodefile`
export PBS_JOBID=$SLURM_JOB_ID
export PBS_O_WORKDIR="$SLURM_SUBMIT_DIR"
export PBS_QUEUE=batch

# Set the max number of threads to use for programs using OpenMP. Should be <= ppn. Does nothing if the program doesn't use OpenMP.
export OMP_NUM_THREADS=$SLURM_CPUS_ON_NODE

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

COLORS=colors.txt
KMER_LEN=17
KMERS=kmers.counts.txt # the count of all shared kmers from the genomes in colors.txt
MAX_DEPTH=30
MIN_COLORS=0
BUBBLES=bubbles$1.kmer-$KMER_LEN.depth-$MAX_DEPTH.minColors-$MIN_COLORS.out
MATRIX=matrix$1.kmer-$KMER_LEN.depth-$MAX_DEPTH.minColors-$MIN_COLORS.out

../kleuren -c $COLORS -b $BUBBLES -k $KMERS -m $MATRIX -d $MAX_DEPTH -n $MIN_COLORS
