'''
This script will take bubbles files and concatenate them into
a single bubble file.
'''
# using the FASTA parser from the BioPython package
from Bio import SeqIO

# parse the arguments
import argparse

# get the Bubble data structure
from bubble import Bubble

# unnecessary?
def parse_bubble_file(bubble_path, bubbles):
    with open(bubble_path) as fh:
        total_bubbles = 0
        # initialize the first bubble
        bubble = Bubble(0)
        for record in SeqIO.parse(fh, 'fasta'):
            tokens = record.description.strip().split()
            bubble_num = int(tokens[1])
            if total_bubbles < bubble_num:
                # add the bubble to bubbles
                bubbles.append(bubble)
                # initialize a new bubble
                bubble = Bubble(bubble_num)
                total_bubbles += 1
            taxa = []
            for taxon in tokens[3::]:
                taxa.append(taxon.replace(',', ''))
            for taxon in taxa:
                bubble.add_path(taxon, record.seq)

def parse_bubble_files(bubble_paths, bubbles):
    for bubble_path in bubble_paths:
        parse_bubble_file(bubble_path, bubbles)

def assign_new_numbers(bubbles):
    bubble_num = 0
    for bubble in bubbles:
        bubble.num = bubble_num
        bubble_num += 1

def print_bubbles(bubbles, out_file):
    with open(out_file, 'w') as fh:
        for bubble in bubbles:
            fh.write(bubble.to_expanded_str())

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('bubble_files', type=str, nargs='+')
    parser.add_argument('-o', '--output')

    args = parser.parse_args()

    bubbles = []
    parse_bubble_files(args.bubble_files, bubbles)
    assign_new_numbers(bubbles)
    print_bubbles(bubbles, args.output)
