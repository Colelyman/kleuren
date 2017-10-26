/*
 * Implementation of vertex.h.
 */

#include "vertex.h"

Vertex::Vertex(string kmer) {
    this->kmer = kmer;
    this->colors = bit_vector();
}

Vertex::Vertex(string kmer, bit_vector colors) {
    this->kmer = kmer;
    this->colors = colors;
}

Vertex::~Vertex() {

}

bool Vertex::operator==(const Vertex& v) const {
    if(this->kmer == v.kmer && this->colors == v.colors) {
        return true;
    }
    else {
        return false;
    }
}

string Vertex::getKmer() const {
    return this->kmer;
}

bit_vector Vertex::getColors() const {
    return this->colors;
}
