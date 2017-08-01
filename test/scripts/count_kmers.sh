#!/bin/bash

DSK=../../thirdparty/dsk/build/bin/dsk
DSK2ASCII=../../thirdparty/dsk/build/bin/dsk2ascii
# check if DSK is installed, and if not exit
if [ -f $DSK ] 
then
    echo "DSK is found at $DSK"
else
    echo "DSK is not found at $DSK, exiting"
    exit
fi

GENOMES=$(ls -m ../data/sim_population/generation-5/*.fa | sed -e 's/ //g;:a;N;$!ba;s/\n//g')
KMER_SIZE=13
H5_FILE=../data/sim_population/sim_population.count.h5
# run DSK on all of the genomes
echo "Count the kmers"
$DSK -file $GENOMES -kmer-size $KMER_SIZE -solidity-kind one -out $H5_FILE -abundance-min 1

OUT_FILE=../data/sim_population/sim_population.count.txt
# dump the kmer counts to a text file
echo "Convert the binary output file to a text file"
$DSK2ASCII -file $H5_FILE -out $OUT_FILE

# remove the count values from the text file, so only the kmers are left
awk '{ print $1 }' $OUT_FILE > $OUT_FILE.tmp && mv $OUT_FILE.tmp $OUT_FILE

# remove the binary output file
rm $H5_FILE
