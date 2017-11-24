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
#include <sdsl/rank_support.hpp>

using std::string;
using sdsl::bit_vector;
using sdsl::rank_support_v;

class Vertex {

    public:
        Vertex(string kmer, size_t numColors);
  
        Vertex(string kmer, bit_vector colors);

        ~Vertex();

        bool operator==(const Vertex& v) const;

		bool operator<(const Vertex& v) const;

        /// Returns the kmer that this Vertex represents
        string getKmer() const;

        static string bitsToString(const unsigned char* kmerBits, size_t kmerSize);

        /// Converts the kmer of type string to a bit-packed unsigned char*.
        static const unsigned char* getKmerBits(string kmer);

        const unsigned char* getKmerBits();

        /// Returns the colors as a bit_vector that contain this Vertex
        bit_vector getColors() const;

		/// Returns the number of colors that contain this Vertex
		unsigned int getNumColors() const;

    private:
        string kmer;

        /// A boolean value that is initialized to false, but when kmerBits is set, bitsSet is
        /// set to true.
        bool bitsSet;
        
        const unsigned char* kmerBits;

        bit_vector colors;

};

#endif
