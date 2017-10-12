/**
 * @class Graph
 *
 * Graph represents the Colored de Bruijn graph for all of the 
 * colors provided. Currently it is implemented as a hash map
 * with the key being a vertex (kmer) and the value being a 
 * bitvector of colors.
 *
 * @author Cole Lyman
 *
 * @date 2017/10/10
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>

#include "vertex.h"

using std::string;
using std::vector;
using std::map;

class Graph {

    public:
        Graph();

        ~Graph();

        /// Returns whether or not a vertex is contained
        bool isVertex(Vertex& v) const;

        /// Returns the vertex of a kmer
        Vertex getVertex(string& kmer) const;

        /// Adds a vertex s to the graph with color c associated
        void addVertex(Vertex& v);

        /// Returns a vector of all of the vertices that neighbor v on the suffix side
        vector<Vertex> getSuffixNeighbors(Vertex& v) const;

        /// Returns a vector of all of the vertices that neighbor v on the prefix side
        vector<Vertex> getPrefixNeighbors(Vertex& v) const;

    private:
        map<string, bit_vector> hashmap;

        /// nucleotides represents the supported IUPAC nucleotide codes
        vector<char> nucleotides = {'A', 'C', 'G', 'T', 'N'};

};

#endif
