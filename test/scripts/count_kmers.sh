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

GENOMES=../data/ebola.fa,../data/flu.fa,../data/marburg.fa,../data/zika.fa
KMER_SIZE=17
H5_FILE=../data/super_viruses.count.h5
# run DSK on all of the genomes
echo "Count the kmers"
$DSK -file $GENOMES -kmer-size $KMER_SIZE -solidity-kind one -out $H5_FILE -abundance-min 1

OUT_FILE=../data/super_viruses.count.txt
# dump the kmer counts to a text file
echo "Convert the binary output file to a text file"
$DSK2ASCII -file $H5_FILE -out $OUT_FILE

# remove the binary output file
rm $H5_FILE
