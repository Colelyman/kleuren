import argparse, copy, pdb
from functools import reduce
import numpy as np
from Bio import SeqIO
from collections import deque

# from kcollections import Kdict

from typing import List, Tuple, Optional

Colors = np.ndarray # List[bool]


class Node:
    def __init__(self, num_colors: int):
        self.colors = np.zeros(num_colors, dtype=np.bool)

    def add_color(self, color_id: int):
        self.colors[color_id] = True

    def num_colors(self):
        return len(np.where(self.colors)[0])

    def __repr__(self):
        return str(self.colors)


NUCLEOTIDES = ['A', 'C', 'G', 'T']


def build_graph(genome_paths: List[str], k: int) -> Tuple[dict, int]:
    graph = {}
    color_id = 0
    for genome_path in genome_paths:
        with open(genome_path, 'r') as genome_fh:
            for chromosome in SeqIO.parse(genome_fh, 'fasta'):
                add_seq(graph, chromosome.seq, color_id, k, len(genome_paths))

        color_id += 1
    return graph, len(genome_paths)


def get_kmers(seq: str, k: int) -> str:
    for i in range(len(seq) - k + 1):
        kmer = str(seq[i:i + k])
        yield kmer.upper()


def add_seq(graph: dict, seq: str, color_id: int, k: int, num_colors: int):
    for kmer in get_kmers(seq, k):
        if kmer not in graph:
            graph[kmer] = Node(num_colors)
        graph[kmer].add_color(color_id)


def get_suffix_neighbors(graph: dict, kmer: str) -> List[str]:
    return [kmer[1:] + suffix for suffix in filter(lambda n: kmer[1:] + n in graph, NUCLEOTIDES)]


def get_prefix_neighbors(graph: dict, kmer: str) -> List[str]:
    return [prefix + kmer[:-1] for prefix in filter(lambda n: n + kmer[:-1] in graph, NUCLEOTIDES)]


def find_bubbles(graph: dict, min_colors: int, min_depth: int = 10, max_depth: int = 30):
    for start, val in graph.items():
        colors = val.colors
        if val.num_colors() >= min_colors and len(get_suffix_neighbors(graph, start)) > 1:
            end = find_end(graph, start, min_colors, min_depth, max_depth)
            if end is None:
                continue
            print(start, end)
            paths = extend_paths(graph, start, end, max_depth)
            bubble_stats(paths)


def bubble_stats(paths: dict):
    present_colors = reduce((lambda x, y: np.array(x) | np.array(y)), [colors for colors in paths.keys()])
    print('Number of present colors:', len(np.where(present_colors)[0]))
    avg_path_length = sum(len(path) for path in paths.values()) / len(paths)
    print('Average path length:', avg_path_length)
    print()


def find_end(graph: dict, start: str, min_colors: int, min_depth: int, max_depth: int) -> Optional[str]:
    start_colors = graph[start].colors
    q = deque()
    depth = 0
    q.append((start, depth))

    while len(q) > 0 and depth < max_depth:
        current, depth = q.popleft()
        for neighbor in get_suffix_neighbors(graph, current):
            if np.array_equal(graph[neighbor].colors, start_colors) and depth >= min_depth:
                return neighbor
            else:
                q.append((neighbor, depth + 1))

    return None


def extend_paths(graph: dict, start: str, end: str, max_depth: int):
    def check_colors(colors, indices):
        return all([colors[i] for i in indices])

    paths = {}
    colors_found = np.copy(~graph[start].colors)
    # print('start colors', graph[start].colors)

    while not np.all(colors_found):
        current_color_index = np.where(~colors_found)[0][0]
        # print('current_color_index', current_color_index, 'colors_found', colors_found)
        path, colors = dfs(graph, start, end, current_color_index, max_depth)
        if colors is None:
            continue
        colors_t = tuple(colors)
        if colors_t in paths:
            print('Existing color set found again in bubble')
        paths[colors_t] = path
        colors_found |= colors

    return paths


def dfs(graph: dict, start: str, end: str, current_color_index: int, max_depth: int) -> Tuple[str, list]:
    def _dfs(current: str, current_color_index: int, intersecting_colors: Colors, path: str, depth: int) -> Tuple[str, list, bool]:
        if depth >= max_depth:
            return '', intersecting_colors, False
        if current == end:
            return path, intersecting_colors, True

        for neighbor in get_suffix_neighbors(graph, current):
            # print('current', current, 'neighbor', neighbor, 'path', path)
            if graph[neighbor].colors[current_color_index]:
               # print(intersecting_colors, graph[neighbor].colors)
               intersecting_colors &= graph[neighbor].colors # and_colors(intersecting_colors, graph[neighbor].colors)
               path += neighbor[-1]
            else:
                continue

            path, intersecting_colors, proceed = _dfs(neighbor, current_color_index, intersecting_colors, path, depth + 1)
            if not proceed:
                path = neighbor[:-1]
            else:
                return path, intersecting_colors, True

        return '', intersecting_colors, False

    intersecting_colors = np.copy(graph[start].colors)
    path, colors, found = _dfs(start, current_color_index, intersecting_colors, '', 0)
    if found:
        return path[:-len(end)], colors
    else:
        return None, None


def and_colors(list_a, list_b):
    return [a and b for a, b in zip(list_a, list_b)]


def or_colors(list_a, list_b):
    return [a or b for a, b in zip(list_a, list_b)]


def visualize(graph):
    print('digraph g {')
    for node in graph:
        print('\t{0} [label="{0}\ncolors: {1}"];'.format(node, graph[node].colors))

    for node in graph:
        for s_neighbor in get_suffix_neighbors(graph, node):
            print('\t{} -> {};'.format(node, s_neighbor))

    print('}')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Builds a CdBG using kcollections')
    parser.add_argument('k', type=int, default=27, help='Kmer size')
    parser.add_argument('genomes', type=str, nargs='+',
                        help='Paths to the genomes to be added to the graph.')

    args = parser.parse_args()

    graph, num_colors = build_graph(args.genomes, args.k)

    # visualize(graph)
    find_bubbles(graph, num_colors)
