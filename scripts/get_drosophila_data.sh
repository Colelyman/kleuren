#!/bin/bash

OUT_DIR=$1

# make the output directory if it doesn't exist
mkdir -p $OUT_DIR

cd $OUT_DIR

# download the genomes to the desired directory (first command line argument)
wget ftp://ftp.flybase.net/genomes/Drosophila_ananassae/dana_r1.05_FB2016_05/fasta/dana-all-chromosome-r1.05.fasta.gz 
mv dana-all-chromosome-r1.05.fasta.gz d_ananassae.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_erecta/dere_r1.05_FB2016_05/fasta/dere-all-chromosome-r1.05.fasta.gz 
mv dere-all-chromosome-r1.05.fasta.gz d_erecta.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_grimshawi/dgri_r1.05_FB2017_02/fasta/dgri-all-chromosome-r1.05.fasta.gz 
mv dgri-all-chromosome-r1.05.fasta.gz d_grimshawi.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_melanogaster/dmel_r6.16_FB2017_03/fasta/dmel-all-chromosome-r6.16.fasta.gz 
mv dmel-all-chromosome-r6.16.fasta.gz d_melanogaster.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_mojavensis/dmoj_r1.04_FB2016_05/fasta/dmoj-all-chromosome-r1.04.fasta.gz 
mv dmoj-all-chromosome-r1.04.fasta.gz d_mojavensis.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_persimilis/dper_r1.3_FB2016_05/fasta/dper-all-chromosome-r1.3.fasta.gz 
mv dper-all-chromosome-r1.3.fasta.gz d_persimilis.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_pseudoobscura/dpse_r3.04_FB2016_05/fasta/dpse-all-chromosome-r3.04.fasta.gz 
mv dpse-all-chromosome-r3.04.fasta.gz d_pseudoobscura.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_sechellia/dsec_r1.3_FB2016_05/fasta/dsec-all-chromosome-r1.3.fasta.gz 
mv dsec-all-chromosome-r1.3.fasta.gz d_sechellia.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_simulans/dsim_r2.02_FB2016_05/fasta/dsim-all-chromosome-r2.02.fasta.gz 
mv dsim-all-chromosome-r2.02.fasta.gz d_simulans.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_virilis/dvir_r1.06_FB2016_05/fasta/dvir-all-chromosome-r1.06.fasta.gz 
mv dvir-all-chromosome-r1.06.fasta.gz d_virilis.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_willistoni/dwil_r1.05_FB2016_05/fasta/dwil-all-chromosome-r1.05.fasta.gz 
mv dwil-all-chromosome-r1.05.fasta.gz d_willistoni.fasta.gz
wget ftp://ftp.flybase.net/genomes/Drosophila_yakuba/dyak_r1.05_FB2016_05/fasta/dyak-all-chromosome-r1.05.fasta.gz 
mv dyak-all-chromosome-r1.05.fasta.gz d_yakuba.fasta.gz

cd -

# build the bwtdisk files for each genome
for genome in $(readlink -m $OUT_DIR/*.fasta.gz);
do
    ./build_bwtdisk.sh $genome
done

# create the color file
./gen_color_file.sh $OUT_DIR

echo "Finished downloading the data, building the .bwtdisk files and generating the color file!"
