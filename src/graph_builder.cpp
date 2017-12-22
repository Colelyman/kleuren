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

    string line, prev;
    while(getline(fh, line)) {
        // check if current line is a header, if so then move to the next line
        if(line[0] == '>') {
            prev = "";
            continue;
        }
        // append line to sequence
        addSequence(prev, line, color);
        prev = line;
    }
    // add the final line of the file to the graph
    addSequence(prev, line, color);

    // close the file
    fh.close();

    return;
}

void GraphBuilder::addSequence(string prev, string line, bit_vector color) {
    if(line.length() > 0 && prev.length() >= kmerLen) {
        for(int i = prev.length() - kmerLen + 1;
                i < prev.length() && i > 0 && kmerLen - (prev.length() - i) <= line.length();
                i++) {
            string kmer = prev.substr(i, prev.length() - i) + line.substr(0, kmerLen - (prev.length() - i));
            if(kmer.length() < kmerLen) {
                break;
            }
            Vertex v = Vertex(kmer, color);
            graph->addVertex(v);
        }

        if(line.length() > kmerLen) {
            // break up the sequence into kmers of length kmerLen
            for(unsigned int i = 0; i < line.length() - kmerLen; i++) {
                Vertex v = Vertex(line.substr(i, kmerLen), color);
                graph->addVertex(v);
            }
        }
    }

    return;
}
