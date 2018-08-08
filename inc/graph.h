/**
 * @class Graph
 *
 * Graph represents the Colored de Bruijn Graph CdBG for all of the
 * colors provided. Currently it is a wrapper around the BloomFilterTrie
 * library for fast, exact queries.
 *
 * @author Cole Lyman
 *
 * @date 2018/5/21
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

extern "C" {
    #include <bft.h>
}

class Graph {

    public:

       Graph(char* bftFileName);

       ~Graph();

       bool isBFTKmer(char* kmer) const;

       BFT_kmer* getBFTKmer(char* kmer) const;

       bool isValidBFTKmer(BFT_kmer* bftKmer) const;

       /// Returns the number of colors that node contains
       uint32_t getNumColors(BFT_kmer* bftKmer) const;

       /// Returns the total number of colors present in the CdBG
       uint32_t getNumColors() const;

       /// Returns the array of colors that node contains
       uint32_t* getColors(BFT_kmer* bftKmer) const;

       /// Returns the file path of the color represented by colorId
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

       /// Returns false if there is a valid node in the nodes array. Otherwise returns true
       bool checkIfEmpty(BFT_kmer* bftKmers) const;

       /// The underlying structure representing the Colored de Bruijn Graph as a
       /// BloomFilterTrie.
       BFT* bft;
};

#endif // GRAPH_H
