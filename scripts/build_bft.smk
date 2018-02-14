from os.path import join

# change the BASE variable to the path that leads to the root of the kleuren repo
BASE = '/home/cole/Code/csl/kleuren'
DSK = BASE + '/thirdparty/dsk/build/bin/dsk'
DUMP = BASE + '/thirdparty/dsk/build/bin/dsk2ascii'
BFT = BASE + '/thirdparty/BloomFilterTrie/bft'

# chage the DIR variable to the path where the genomes are stored (must be in fasta
# format, be gzipped, and have the suffix ".fasta.gz")
DIR = '/home/cole/Code/csl/kleuren/test/data/'
COLOR_FILE = DIR + 'colors.txt'
BFT_FILE = DIR + 'bft.out'
KMER_FILE = DIR + 'kmer.bft.out'

KMER_LEN = 18 
ABUNDANCE_MIN = 1
ZIP_PAT = '{taxon}.fasta.gz'
DIR_PAT = '{taxon}/'
TMP_PAT = '{taxon}.tmp'
H5_PAT = '{taxon}.h5'
KMER_PAT = '{taxon}.kmers.txt'
KMER_GZ_PAT = '{taxon}.kmers.txt.gz'

TAXA, = glob_wildcards(join(DIR, ZIP_PAT))

rule all:
    input:
        expand(join(DIR, KMER_GZ_PAT), taxon=TAXA), BFT_FILE

rule count_kmers:
    input:
        ZIP_PAT
    output:
        temp(H5_PAT), temp(TMP_PAT)
    shell:
        'mkdir -p {wildcards.taxon}.tmp && ' +
        DSK + ' -kmer-size ' + str(KMER_LEN) + ' -file {input} -out-tmp {wildcards.taxon}.tmp -abundance-min ' +
        str(ABUNDANCE_MIN) + ' -out {output[0]}'

rule dump_kmers:
    input:
        H5_PAT
    output:
        temp(KMER_PAT)
    shell:
        DUMP + ' -file {input} -out {output}'

rule gzip_counts:
    input:
        KMER_PAT
    output:
        KMER_GZ_PAT
    shell:
        'gzip < {input} > {output}'

rule compile_colors:
    input:
        expand(join(DIR, KMER_PAT), taxon=TAXA)
    output:
        colors = COLOR_FILE, bft = BFT_FILE, kmers = KMER_FILE
    run:
        with open(output.colors, 'w') as out:
            for i in input:
                #line = i + '\t' + i.split('/')[-1].split('.')[0] + '\n'
                #out.write(line)
                out.write(i + '\n')
        shell(BFT + ' build ' + str(KMER_LEN) + ' kmers {output.colors} {output.bft} -extract_kmers kmers {output.kmers}')
