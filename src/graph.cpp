/*
 * Implementation of graph.h.
 */

#include "graph.h"

Graph::Graph() {
    numColors = 0;
}

Graph::~Graph() {
    // deallocate all of the keys in hashmap
    int countElements = 0;
    while(hashmap.size() > 0) {
        auto element = hashmap.begin();
        if(element->first != NULL) {
            countElements++;
            free(const_cast<unsigned char*>(element->first));
        }
        hashmap.erase(element);
    }
}

bool Graph::isVertex(Vertex& v) const {
    auto vertexPair = hashmap.find(v.getKmerBits());
    if(vertexPair != hashmap.end()) {
        // check if the bit_vectors match up
        bit_vector existingColors = vertexPair->second;
        bit_vector andedColors = v.getColors();
        andedColors &= existingColors;
        andedColors ^= existingColors;

        // perform a rank query to see if any of the bits are set in
        // andedColors. If bits are set, then that means v is not a 
        // vertex in the graph, otherwise v is a vertex.
        rank_support_v<> rs(&andedColors);
        bit_vector::size_type numSetBits = rs.rank(andedColors.size());
        if(numSetBits == 0) {
            return true;
        }
    }

    return false;
}

bool Graph::isKmer(string& kmer) const {
    const unsigned char* kmerBits = Vertex::getKmerBits(kmer);
    bool exists = !(hashmap.find(kmerBits) == hashmap.end());
    free(const_cast<unsigned char*>(kmerBits));
    return exists;
}

Vertex Graph::getVertex(string& kmer) const {
    bit_vector colors(0, 0);
    Vertex v = Vertex("", colors);
    const unsigned char* kmerBits = Vertex::getKmerBits(kmer);
    if(hashmap.find(kmerBits) != hashmap.end()) { // the kmer exists in the graph
        v = Vertex(kmer, hashmap.at(kmerBits));
    }
    free(const_cast<unsigned char*>(kmerBits));

    return v;
}

void Graph::addVertex(Vertex& v) {
    // check if the vertex already exists
    auto vertex = hashmap.find(v.getKmerBits());
    if(vertex != hashmap.end()) { // vertex exists
        // bitwise AND the existing bit_vector with the new bit_vector
        bit_vector andedColors = vertex->second;
        andedColors &= v.getColors();

        // reassign the new bit_vector to the kmer in the graph
        hashmap[v.getKmerBits()] = andedColors;
        free(const_cast<unsigned char*>(v.getKmerBits()));
    }
    else { // vertex doesn't exist, thus add it to the graph
        hashmap[v.getKmerBits()] = v.getColors();
    }
}

vector<Vertex> Graph::getSuffixNeighbors(Vertex& v) const {
    vector<Vertex> vertices;
    // strip off the first character from the kmer
    const char* kmer = v.getKmer().substr(1).c_str();
    char* prefix = (char*) malloc(strlen(kmer) + 1);
    strcpy(prefix, kmer);
    size_t index = strlen(prefix);
    prefix[index + 1] = '\0';
    // iterate over each nucleotide code and append it to the kmer
    for(const char nucleotide : nucleotides) {
        // append the nucleotide to the kmer
        prefix[index] = nucleotide;
        // TODO optimize to just use c-strings
        string prefixString = string(prefix);
        Vertex vertex = Vertex(prefixString, v.getColors());
        if(this->isVertex(vertex)) { // check if the vertex exists
            vertices.push_back(vertex);
        }
    }
    free(prefix);
    return vertices;
}

bool Graph::hasSuffixNeighbors(Vertex& v) const {
  if(getSuffixNeighbors(v).size() > 0) {
      return true;
  }
  else {
      return false;
  }
}

vector<Vertex> Graph::getPrefixNeighbors(Vertex& v) const {
    vector<Vertex> vertices;
    // strip off the last character from the kmer
    string kmer = v.getKmer().substr(0, v.getKmer().length() - 1);
    kmer.insert(0, "N");
    // iterate over each nucleotide code and append it to the kmer
    for(char nucleotide : nucleotides) {
        // prepend the nucleotide to the kmer
        kmer[0] = nucleotide;
        Vertex vertex = getVertex(kmer);
        /// TODO check if the vertex's colors match up with the neighbors
        if(vertex.getKmer() != "") { // check if the vertex exists
            vertices.push_back(vertex);
        }
    }
    return vertices;
}

bool Graph::hasPrefixNeighbors(Vertex& v) const {
  if(getPrefixNeighbors(v).size() > 0) {
      return true;
  }
  else {
      return false;
  }
}

size_t Graph::getSize() const {
    return hashmap.size();
}

void Graph::setNumColors(size_t numColors) {
    this->numColors = numColors;
}

string Graph::toString() {
    for(auto const& element : hashmap) {
        printf("kmer is: %s at: %p\n", Vertex::bitsToString(element.first, kmerLen).c_str(), element.first);
    }
    return "";
}
