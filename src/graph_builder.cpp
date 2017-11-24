/*
 * Implementation of graph_builder.h
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "graph_builder.h"

using std::cerr;
using std::endl;

GraphBuilder::GraphBuilder(Graph* graph, unsigned int kmerLen) {
    this->graph = graph;
    this->kmerLen = kmerLen;
}

void GraphBuilder::addColor(string filePath, bit_vector color) {
    clock_t start = clock();
    string suffix = filePath.substr(filePath.rfind("."));
    // check if the file format is supported
    if(suffix == ".fa" || suffix == ".fasta" || suffix == ".fna") {
        parseFasta(filePath, color);
    }
    else {
        cerr << "File type: " << suffix << " is not supported as a sequence file type." << endl;
        cerr << "Supported file types are: fa, fasta, and fna." << endl;
        exit(1);
    }
    cerr << "Added color " << filePath << " in: " << (double)(clock() - start)/CLOCKS_PER_SEC << " seconds" << endl;
}

void GraphBuilder::parseFasta(string filePath, bit_vector color) {
    std::ios::sync_with_stdio(false);
    ifstream fh;
    // open the fasta file
    fh.open(filePath);

    if(!fh.is_open()) {
        cerr << "There was a problem opening file: " << filePath << endl;
        exit(1);
    }

    string seq, line;
    seq.reserve(1000000);
    while(getline(fh, line)) {
        // check if current line is a header, if so then move to the next line
        if(line[0] == '>' && !seq.empty()) {
            addSequence(seq, color);
            seq.clear();
            continue;
        }
        // append line to sequence
        seq.append(line);
    }
    // add the final sequence of the file to the graph
    addSequence(seq, color);

    // close the file
    fh.close();

    return;
}

void GraphBuilder::addSequence(string seq, bit_vector color) {
    // break up the sequence into kmers of length kmerLen
    for(unsigned int i = 0; i < seq.length() - kmerLen; i++) {
        Vertex v = Vertex(seq.substr(i, kmerLen), color);
        graph->addVertex(v);
    }

    return;
}
