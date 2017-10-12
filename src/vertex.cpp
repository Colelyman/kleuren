/*
 * Implementation of vertex.h.
 */

#include "vertex.h"

Vertex::Vertex(string kmer, bit_vector colors) {

}

Vertex::~Vertex() {

}

string Vertex::getKmer() const {
    return this->kmer;
}

bit_vector Vertex::getColors() const {
    return this->colors;
}
