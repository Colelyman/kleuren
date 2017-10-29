/*
 * Implementation of graph_builder.h
 */

#include <iostream>
#include <stdlib.h>

#include "graph_builder.h"

using std::cerr;
using std::endl;

GraphBuilder::GraphBuilder(Graph* graph, unsigned int kmerLen) {
    this->graph = graph;
    this->kmerLen = kmerLen;
}

void GraphBuilder::addColor(string filePath, bit_vector color) {
    string suffix = filePath.substr(filePath.rfind("."));
    // check if the file format is supported
    if(suffix == "fa" || suffix == "fasta" || suffix == "fna") {
        parseFasta(filePath, color);
    }
    else {
        cerr << "File type: " << suffix << " is not supported as a sequence file type." << endl;
        cerr << "Supported file types are: fa, fasta, and fna." << endl;
        exit(1);
    }
}

void GraphBuilder::parseFasta(string filePath, bit_vector color) {
    ifstream fh;
    // open the fasta file
    fh.open(filePath);

    string seq, line;
    while(getline(fh, line)) {
        // check if current line is a header, if so then add the sequence to the graph
        if(line[0] == '>') {
            addSequence(seq, color);
            seq.clear();
            continue;
        }
        // append line to sequence
        seq += line;
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
