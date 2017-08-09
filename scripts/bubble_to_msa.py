'''
This script will take the bubbles from a bubble file and create a
super-matrix will
run a Multiple Sequence Alignment (MSA) by performing
'''
# using the MAFFT commandline from the BioPython package
from Bio.Align.Applications import MafftCommandline

# using the FASTA parser and alignment writer from the BioPython package
from Bio import SeqIO, AlignIO
from Bio.Align import MultipleSeqAlignment
from Bio.Alphabet import generic_dna
from Bio.Seq import Seq
from Bio.SeqRecord import SeqRecord

# parse the arguments
import argparse

import os
import glob

class Bubble:
    def __init__(self, bubble_num):
        self.num = bubble_num
        self.paths = {}

    def add_path(self, taxon, path):
        self.paths[taxon] = path

    def __str__(self):
        out = ''
        for taxon, path in self.paths.items():
            out += '> ' + taxon + '\n'
            out += str(path) + '\n'
        return out

def process_bubble(bubble, out_dir):
    path = os.path.join(out_dir, 'bubble-' + str(bubble.num) + '.fasta')
    with open(path, 'w') as fh:
        fh.write(str(bubble))
    run_msa(path, out_dir, str(bubble.num))

def run_msa(fasta_path, out_dir, bubble_num):
    mafft_cline = MafftCommandline(input=fasta_path)

    # run MAFFT
    stdout, stderr = mafft_cline()

    # write the MSA to a file
    with open(os.path.join(out_dir, 'msa-' + bubble_num + '.fasta'), 'w') as fh:
        fh.write(stdout)

def parse_bubble_file(bubble_path, out_dir):
    with open(bubble_path) as fh:
        total_bubbles = 0
        # initialize the first bubble
        bubble = Bubble(0)
        for record in SeqIO.parse(fh, 'fasta'):
            tokens = record.description.strip().split()
            bubble_num = int(tokens[1])
            if total_bubbles < bubble_num:
                # process the previous bubble
                process_bubble(bubble, out_dir)
                # initialize a new bubble
                bubble = Bubble(bubble_num)
                total_bubbles += 1
            taxa = []
            for taxon in tokens[3::]:
                taxa.append(taxon.replace(',', ''))
            for taxon in taxa:
                bubble.add_path(taxon, record.seq)

def concatenate_msa(out_dir):
    with open(os.path.join(out_dir, 'supermatrix-msa.fasta'), 'w') as fh:
        # set the order of the taxa based on the first MSA file
        taxa = {}
        for record in SeqIO.parse(os.path.join(out_dir, 'msa-0.fasta'), 'fasta'):
            taxa[record.id] = Seq('', generic_dna)
        # get each MSA file and concatenate it to the supermatrix
        for msa_file in glob.glob(os.path.join(out_dir, 'msa-*.fasta')):
            alignment = SeqIO.to_dict(SeqIO.parse(os.path.join(out_dir, msa_file), 'fasta'))
            for taxon, seq in taxa.items():
                taxa[taxon] += alignment[taxon].seq
                #seq.append(str(alignment[taxon].seq))
        # write the supermatrix to the file
        msa = MultipleSeqAlignment([], alphabet=generic_dna)
        for taxon, seq in taxa.items():
            print(type(seq))
            msa.append(SeqRecord(seq, id=taxon))
        AlignIO.write(msa, fh, 'nexus')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('bubble_file', type=str, help='The path to the bubble file in which the MSA will be computed.')
    parser.add_argument('out_dir', type=str, help='The path to the directory in which the individual MSAs will be written.')

    args = parser.parse_args()

    parse_bubble_file(args.bubble_file, args.out_dir)

    concatenate_msa(args.out_dir)
