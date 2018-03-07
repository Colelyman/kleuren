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
#include <map>
#include <list>

#include "bubble.h"
#include "graph.h"
#include "color.h"
#include "path.h"

extern "C" {
    #include <bft/bft.h>
}

using std::string;
using std::map;
using std::list;

/// A comparator for two uint32_t arrays (representing colors in the graph. Used in the
/// extendPaths method so that the arrays can be added to a map.
struct uint32Cmp {
    bool operator()(const uint32_t* a, const uint32_t* b) {
        // check the length of the arrays
        if(a[0] < b[0]) {
            return true;
        }
        else if(a[0] > b[0]) {
            return false;
        }
        else {
            return comp_uint32(a, b);
        }
    }
};

class BubbleBuilder {

    public:

        BubbleBuilder(Graph* graph);

        /**
         * Builds the bubble starting at startBftKmer.
         * @param startBftKmer the kmer to start building the bubble
         * @param numColors the number of colors necessary in order for a kmer to be considered as
         * an endBftKmer
         * @param maxDepth how many levels deep to search for endBftKmers and paths
         * @return the bubble that starts with startBftKmer; if no bubble is found an empty bubble
         * is returned
         */
        Bubble build(BFT_kmer* startBftKmer, uint32_t numColors, uint32_t maxDepth);

        /** 
         * Finds the ending kmer, which is the next kmer that contains all of the colors.
         * @param startBftKmer the kmer to start the search with
         * @param numColors the number of colors necessary in order for a vertex to be considered.
         * @param maxDepth how many levels deep to search for the endBftKmer
         * @return the next kmer that is present in numColors (or more) colors, but if there is no kmer 
         * that is present in numColors (or more) it will return null 
         */
        BFT_kmer* findEndBftKmer(BFT_kmer* startBftKmer, uint32_t numColors, uint32_t maxDepth);

        /**
         * Extends the paths between startBftKmer and endBftKmer for all colors. The function will
         * search for the paths between the startBftKmer and the endBftKmer, or until the maxDepth is
         * reached in which case an empty string is set as the path.
         * @param startBftKmer the kmer to start the path with
         * @param endBftKmer the kmer to finish the path with
         * @param maxDepth the maxmimum recursive depth for the underlying recursive function to search
         * for a path
         * @return the paths for each color between startKmer and endKmer
         */
        Bubble extendPaths(BFT_kmer* startBftKmer, BFT_kmer* endBftKmer, uint32_t maxDepth);

    private:

        bool recursiveExtend(BFT_kmer* currentBftKmer, uint32_t currentColor, uint32_t** intersectingColors, BFT_kmer* endBftKmer, string& path, uint32_t depth, uint32_t maxDepth);

        Graph* graph;
};

#endif // BUBBLE_BUILDER_H

