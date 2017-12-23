/**
 * @class BubbleBuilder
 *
 * BubbleBuilder builds Bubble objects. 
 *
 * @author Cole Lyman
 *
 * @date 2017/6/22
 *
 */

#ifndef BUBBLE_BUILDER_H
#define BUBBLE_BUILDER_H

#include <string>
#include <memory>
#include <map>

#include "bubble.h"
#include "graph.h"
#include "color.h"
#include "path.h"

using std::string;
using std::shared_ptr;
using std::map;

class BubbleBuilder {

    public:

	BubbleBuilder(Graph* graph);

        /// Returns the Bubble built starting at startVertex
        Bubble build(Vertex& startVertex, unsigned int numColors, unsigned int maxDepth);

        /** 
         * Finds the index of the ending kmer, which is the next kmer 
         * that contains all of the colors.
         * @param startKmer the kmer to start searching for
         * @param numColors the number of colors necessary in order for a vertex to be considered.
         * @return the next kmer that is present in numColors (or more) colors, but if there is no kmer 
         * that is present in numColors (or more) it will return null 
         */
        Vertex findEndVertex(Vertex& startVertex, unsigned int numColors);

        /**
         * Extends the path between startKmer and endKmer for a given color. The function will
         * search for the path between the startKmer and the endKmer, or until the maxDepth is 
         * reached in which an empty string is returned as the path.
         * @param startKmer the kmer to start the path with
         * @param endKmer the kmer to finish the path with
         * @param color the Color to use in order to extend the path
         * @param maxDepth the maxmimum recursive depth for the underlying recursive function
         * @return the path for color between startKmer and endKmer
         */
        map<bit_vector, string> extendPaths(Vertex& startVertex, Vertex& endVertex, unsigned int maxDepth);

    private:

	vector<Vertex> getNeighbors(vector<Vertex> vertices);

	bool recursiveExtend(Vertex& currentVertex, Vertex& endVertex, map<bit_vector, string>& paths, set<Vertex>& visited, unsigned int depth, unsigned int maxDepth);

	Graph* graph;
};

#endif // BUBBLE_BUILDER_H
        
