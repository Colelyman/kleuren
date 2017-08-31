# This script will use the ETE Toolkit's compare feature to
# find the distance between two trees.
# The input parameters to this script are the files to the trees
# in Newick format. The first tree is assumed to be the reference.

# activate the environment (assumes conda is installed and the kleuren
# conda environment has been configured)
source activate kleuren

REF=$1
OTHER=$2

ete3 compare --unrooted -t $OTHER -r $REF

# identical trees should return 0
