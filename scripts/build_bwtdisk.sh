#!/bin/bash

#SBATCH --time=00:30:00   # walltime
#SBATCH --ntasks=1   # number of processor cores (i.e. tasks)
#SBATCH --nodes=1   # number of nodes
#SBATCH --mem-per-cpu=4G   # memory per CPU core

# Compatibility variables for PBS. Delete if not needed.
export PBS_NODEFILE=`/fslapps/fslutils/generate_pbs_nodefile`
export PBS_JOBID=$SLURM_JOB_ID
export PBS_O_WORKDIR="$SLURM_SUBMIT_DIR"
export PBS_QUEUE=batch

# Set the max number of threads to use for programs using OpenMP. Should be <= ppn. Does nothing if the program doesn't use OpenMP.
export OMP_NUM_THREADS=$SLURM_CPUS_ON_NODE

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

# This script will build the necessary bwtdisk file from a given fasta file.
# This script must be run from the `./kleuren/scripts` directory, and bwtdisk
# must be installed in order for it to work.
#
# There is exactly one input parameter, the fasta file in which to create a
# BWT for. The file will be written to the same directory as the input file.

# get the absolute path of the input file (the first argument)
FILE_PATH=$(readlink -f $1)

# check if the file is compressed using gzip, if so, decompress it
if [[ "${FILE_PATH##*.}" == *"gz"* ]]; then
    FASTA_FILE="${FILE_PATH%.*}"
    gunzip -c $FILE_PATH > $FASTA_FILE
else
    FASTA_FILE=$FILE_PATH
fi

cd ../thirdparty/dbgfm/

./run_bwtdisk.sh $FASTA_FILE

# delete the decompressed file if it was indeed decompresed
if [[ "${FILE_PATH##*.}" == *"gz"* ]]; then
    rm $FASTA_FILE
fi
