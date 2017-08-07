#!/bin/bash

# this script generates a population of mutated genomes based off of a reference using mutatrix 

function usage {
    echo '
  ________                  __________                   .__          __  .__               
 /  _____/  ____   ____     \______   \____ ______  __ __|  | _____ _/  |_|__| ____   ____  
/   \  ____/ __ \ /    \     |     ___/  _ \|____ \|  |  \  | \__  \|   __\  |/  _ \ /    \ 
\    \_\  \  ___/|   |  \    |    |  (  <_> )  |_> >  |  /  |__/ __ \|  | |  (  <_> )   |  \
 \______  /\___  >___|  /____|____|   \____/|   __/|____/|____(____  /__| |__|\____/|___|  /
        \/     \/     \/_____/              |__|                   \/                    \/ 
 '
    echo "Create a population of mutated genomes from a reference with a known tree"
    echo "This script uses [mutatrix](https://github.com/ekg/mutatrix) and"
    echo "optionally [dot- GraphVix](http://www.graphviz.org/)."
    echo -e "\t[Required arguments]"
    echo -e "\t-n,--num_gen\t\tthe number of generations to produce"
    echo -e "\t-g,--genome\t\tthe reference genome to mutate, represents the root ancestor"
    echo -e "\t-o,--output\t\tthe path to the directory in which the generated genomes will be written to"
    echo -e "\n\t[Optional argument]"
    echo -e "\t-s,--seed\t\tthe random seed to pass to mutatrix"
    echo -e "\t-h,--help\t\tprint this help message"
    exit 1;
}

# parse the command line parameters
while :; do
    case $1 in
        -n|--num_gen) 
            N=$2
            shift
            ;;
        -g|--genome) 
            REF=$2
            shift
            ;;
        -o|--output)
            O=$2
            shift
            ;;
        -s|--seed)
            SEED=-g $2
            shift
            ;;
        -h|--help) 
            usage
            ;;
        -?*) 
            echo "Invalid option $1" >&2 && usage
            exit 1
            ;;
        *)
            break
    esac
    shift
done

echo "N $N"
echo "REF $REF"

# define the path to mutatrix
MUTATRIX=../thirdparty/mutatrix/mutatrix

# create the children array with REF as the only value
CHILDREN[0]=$REF

# create the output directory if not already created
mkdir -p $O

TREE_FILE=$O/tree.dot
TREE_PIC=$O/tree.png
echo -e "digraph phylogeneticTree {\n\tnode [shape=plaintext];\n" > $TREE_FILE

# iterate over each generation
for ((i=1;i<=$N;i++))
do
    OUT_PREFIX=$O/generation-$i/
    # iterate over the "parents" (the genomes generated in the previous generation)
    for ((j=0;j<${#CHILDREN[*]};j++)) #child in $CHILDREN
    do
        VCF=mutants.generation-$i.child-$j.vcf
        FILE_PREFIX=generation-$i.child-$j
        mkdir -p $OUT_PREFIX
        PARENT=${CHILDREN[$j]}
        # mutate the genome and create two children!! 
        $MUTATRIX -n 2 $SEED -S $FILE_PREFIX. -P $OUT_PREFIX $PARENT > $VCF
        # write the relationship to the TREE_FILE
        P=$(basename $PARENT | awk '{split($0, p, ":"); print p[1]}')
        echo -e "\t\"$P\" -> \"$FILE_PREFIX.1\";" >> $TREE_FILE
        echo -e "\t\"$P\" -> \"$FILE_PREFIX.2\";" >> $TREE_FILE
        # move the vcf file to the respective generation directory
        mv $VCF $OUT_PREFIX$VCF
    done
    CHILDREN=($OUT_PREFIX*.fa)
done

echo -e "\n}" >> $TREE_FILE

# check if GraphViz dot program is installed
if hash dot 2>/dev/null; then
    # export the dot file to png
    dot -Tpng $TREE_FILE -o $TREE_PIC
fi

