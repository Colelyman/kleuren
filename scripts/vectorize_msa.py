'''
This script will vectorize a MSA of a bubble.
'''
import argparse
import glob
import os
import numpy as np

from Bio import SeqIO


def parse_MSAs(bubble_dir):
    vectorized_bubbles = []
    taxa = []
    for record in SeqIO.parse(
            os.path.join(bubble_dir, 'msa-0.fasta'), 'fasta'):
        taxa.append(record.id)
    for msa_file in glob.glob(os.path.join(bubble_dir, 'msa-*.fasta')):
        vectorized_bubbles.append(vectorize_MSA(parse_MSA(msa_file), taxa))
    return vectorized_bubbles


def parse_MSA(msa_file):
    return SeqIO.to_dict(SeqIO.parse(msa_file, 'fasta'))


def vectorize_MSA(alignment, taxa):
    vector = np.ndarray(shape=(len(taxa), len(taxa)), dtype=int)
    for i, taxon1 in enumerate(taxa):
        for j, taxon2 in enumerate(taxa):
            if i == j:
                vector[i][j] = 0
            else:
                vector[i][j] = hamming_dist(
                    alignment[taxon1].seq,
                    alignment[taxon2].seq)
    return vector


def hamming_dist(seq1, seq2):
    if len(seq1) != len(seq2):
        raise ValueError('The lengths of the sequences vary.')
    return sum(char1 != char2 for char1, char2 in zip(seq1, seq2))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        'bubble_dir',
        type=str,
        help='The path to the directory in which the individual \
        MSAs are found.')

    args = parser.parse_args()

    print(parse_MSAs(args.bubble_dir))
