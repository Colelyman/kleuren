/*
 * Implementation of graph.h.
 */

#include "graph.h"

Graph::Graph() {

}

Graph::~Graph() {

}

bool Graph::isVertex(Vertex& v) const {
    auto vertex = hashmap.find(v.getKmer());
    if(vertex != hashmap.end()) {
        /// TODO check if the bit_vectors match up...
        return true;
    }
    else {
        return false;
    }
}

Vertex Graph::getVertex(string& kmer) const {
    /// TODO get the number of colors
    bit_vector colors(0, 0);
    Vertex v = Vertex("", colors);
    if(hashmap.find(kmer) != hashmap.end()) { // the kmer exists in the graph
        v = Vertex(kmer, hashmap.at(kmer));
    }

    return v;
}

void Graph::addVertex(Vertex& v) {
    // check if the vertex already exists
    auto vertex = hashmap.find(v.getKmer());
    if(vertex != hashmap.end()) { // vertex exists
        // bitwise AND the existing bit_vector with the new bit_vector
        bit_vector andedColors = vertex->second;
        andedColors &= v.getColors();

        // reassign the new bit_vector to the kmer in the graph
        hashmap[v.getKmer()] = andedColors;
    }
    else { // vertex doesn't exist, thus add it to the graph
        hashmap[v.getKmer()] = v.getColors();
    }
}

vector<Vertex> Graph::getSuffixNeighbors(Vertex& v) const {
    vector<Vertex> vertices;
    // strip off the first character from the kmer
    string kmer = v.getKmer().substr(1);
    // iterate over each nucleotide code and append it to the kmer
    for(const char nucleotide : nucleotides) {
        // append the nucleotide to the kmer
        kmer.append(&nucleotide);
        Vertex vertex = getVertex(kmer);
        if(vertex.getKmer() != "") { // check if the vertex exists
            vertices.push_back(vertex);
        }
        // strip off the last character from the kmer
        kmer = kmer.substr(0, kmer.length() - 1);
    }
    return vertices;
}

vector<Vertex> Graph::getPrefixNeighbors(Vertex& v) const {
    vector<Vertex> vertices;
    // strip off the last character from the kmer
    string kmer = v.getKmer().substr(0, kmer.length() - 1);
    // iterate over each nucleotide code and append it to the kmer
    for(char nucleotide : nucleotides) {
        // prepend the nucleotide to the kmer
        kmer.insert(0, 1, nucleotide);
        Vertex vertex = getVertex(kmer);
        if(vertex.getKmer() != "") { // check if the vertex exists
            vertices.push_back(vertex);
        }
        // strip off the first character from the kmer
        kmer = kmer.substr(1, kmer.length() - 1);
    }
    return vertices;
}

