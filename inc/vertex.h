/**
 * @class Vertex
 * 
 * Vertex represents a vertex in the Colored de Bruijn graph.
 * It is simply a string and a bit_vector that represents a 
 * Color in the Graph.
 *
 * @author Cole Lyman
 *
 * @date 2017/10/10
 *
 */

#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <sdsl/bit_vectors.hpp>

using std::string;
using sdsl::bit_vector;

class Vertex {

    public:
        Vertex(string kmer, bit_vector colors);

        ~Vertex();

        /// Returns the kmer that this Vertex represents
        string getKmer() const;

        /// Returns the colors as a bit_vector that contain this Vertex
        bit_vector getColors() const;

    private:
        string kmer;

        bit_vector colors;

};

#endif
