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
#include <iostream>

extern "C" {
    #include <bft/bft.h>
}

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;

class Graph {

    public:

       Graph(char* bftFileName);

       ~Graph();
       
       bool isBFTKmer(char* strKmer) const;

       BFT_kmer* getBFTKmer(char* strKmer) const;

       bool isValidBFTKmer(BFT_kmer* bftKmer) const;

       void setMarking();

       void clearMarking();

       void markBFTKmer(BFT_kmer* bftKmer);

       bool isMarkedBFTKmer(BFT_kmer* bftKmer) const;

       uint32_t getNumColors(BFT_kmer* bftKmer) const;

       uint32_t getNumColors() const;

       uint32_t* getColors(BFT_kmer* bftKmer) const;

       char* getColorFilePath(uint32_t colorId) const;

       /// Returns a vector of all of the vertices that neighbor v on the suffix side
       BFT_kmer* getSuffixNeighbors(BFT_kmer* bftKmer) const;

       /// Returns the boolean value according to if the vertex has suffix neighbors
       bool hasSuffixNeighbors(BFT_kmer* bftKmer) const;

       /// Returns a vector of all of the vertices that neighbor v on the prefix side
       BFT_kmer* getPrefixNeighbors(BFT_kmer* bftKmer) const;

       /// Returns the boolean value according to if the vertex has prefix neighbors
       bool hasPrefixNeighbors(BFT_kmer* bftKmer) const;

    private:

        bool checkIfEmpty(BFT_kmer* bftKmers) const;

        /// The underlying structure representing the Colored de Bruijn Graph as a
        /// BloomFilterTrie.
        BFT* bft;

};

#endif
