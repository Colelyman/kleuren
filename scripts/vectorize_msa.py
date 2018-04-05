'''
This script will vectorize and display MSAs of bubbles.
'''
import argparse
import glob
import os
import numpy as np

from Bio import SeqIO

from sklearn.decomposition import PCA
from sklearn.manifold import MDS
import matplotlib.pyplot as plt


def parse_MSAs(bubble_dir):
    vectorized_bubbles = []
    num_labels = []
    taxa = []
    taxa_names = []
    for record in SeqIO.parse(
            os.path.join(bubble_dir, 'msa-0.fasta'), 'fasta'):
        taxa.append(record.id)
        taxa_names.append(record.description)
    for msa_file in glob.glob(os.path.join(bubble_dir, 'msa-*.fasta')):
        vectorized_bubbles.append(vectorize_MSA(parse_MSA(msa_file), taxa))
        num_labels.append(np.linspace(0, len(taxa), len(taxa)))
    return np.array(vectorized_bubbles).reshape((-1, len(taxa))),\
        np.array(num_labels).reshape((-1, len(taxa))), taxa_names


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


def rand_jitter(arr):
    stdev = .003*(max(arr)-min(arr))
    return arr + np.random.randn(len(arr)) * stdev


def reduce_dim_pca(vectorized_bubbles, num_labels, taxa_names, n_components):
    pca = PCA(n_components=n_components)
    projected_bubbles = pca.fit_transform(vectorized_bubbles)
    print(projected_bubbles.shape)
    flat_labels = num_labels.flatten()
    plot(projected_bubbles, flat_labels, num_labels, taxa_names, 2, 3)


def reduce_dim_mds(vectorized_bubbles, num_labels, n_components):
    mds = MDS(n_components=n_components)
    projected_bubbles = mds.fit_transform(vectorized_bubbles)
    print(projected_bubbles)


def plot(projected_bubbles, flat_labels, num_labels, taxa_names, c1, c2):
    plt.scatter(rand_jitter(projected_bubbles[:, c1]),
                rand_jitter(projected_bubbles[:, c2]),
                c=flat_labels, edgecolor='none', alpha=0.9,
                cmap=plt.cm.get_cmap('nipy_spectral', len(num_labels[0])))
    plt.xlabel('PC ' + str(c1 + 1))
    plt.ylabel('PC ' + str(c2 + 1))
    plt.title('Reduced Dimensions of each Path in a Set of Bubbles')
    cb = plt.colorbar()
    cb.set_label('Species', rotation=270)
    cb.set_ticks(num_labels[0])
    cb.set_ticklabels(taxa_names)
    plt.show()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        'bubble_dir',
        type=str,
        help='The path to the directory in which the individual \
        MSAs are found.')
    parser.add_argument(
        'output',
        type=str,
        help='The path to the file that will contain the pickled output.')

    args = parser.parse_args()

    vectorized_bubbles, num_labels, taxa_names = parse_MSAs(args.bubble_dir)
    reduce_dim_pca(vectorized_bubbles, num_labels, taxa_names, 12)
