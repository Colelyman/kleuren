/**
 * @class BubbleBuilder
 *
 * BubbleBuilder builds Bubble objects.
 *
 * @author Cole Lyman
 *
 * @date 2018/5/22
 *
 */

#ifndef BUBBLE_BUILDER_H
#define BUBBLE_BUILDER_H

#include <string>
#include <map>
#include <list>

#include "bubble.h"
#include "bubble_stats.h"
#include "graph.h"
#include "filter.h"

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

        BubbleBuilder(Graph* graph, BubbleStats* bubbleStats);

        /**
         * Builds the bubble starting at startBFTKmer.
         * @param startBFTKmer the kmer to start building the bubble
         * @param numColors the number of colors necessary in order for a kmer to be considered as
         * an endBFTKmer
         * @param maxDepth how many levels deep to search for endBFTKmers and paths
         * @return the bubble that starts with startBFTKmer; if no bubble is found an empty bubble
         * is returned
         */
        Bubble build(BFT_kmer* startBFTKmer, uint32_t numColors, uint32_t maxDepth);

        /**
         * Finds the ending kmer, which is the next kmer that contains all of the colors.
         * @param startBFTKmer the kmer to start the search with
         * @param numColors the number of colors necessary in order for a vertex to be considered.
         * @param maxDepth how many levels deep to search for the endBFTKmer
         * @return the next kmer that is present in numColors (or more) colors, but if there is no kmer
         * that is present in numColors (or more) it will return null
         */
        BFT_kmer* findEndBFTKmer(BFT_kmer* startBFTKmer, uint32_t numColors, uint32_t maxDepth);

        /**
         * Extends the paths between startBFTKmer and endBFTKmer for all colors. The function will
         * search for the paths between the startBFTKmer and the endBFTKmer, or until the maxDepth is
         * reached in which case an empty string is set as the path.
         * @param startBFTKmer the kmer to start the path with
         * @param endBFTKmer the kmer to finish the path with
         * @param maxDepth the maxmimum recursive depth for the underlying recursive function to search
         * for a path
         * @return the paths for each color between startKmer and endKmer
         */
        Bubble extendPaths(BFT_kmer* startBFTKmer, BFT_kmer* endBFTKmer, uint32_t maxDepth);

        bool recursiveExtend(BFT_kmer* currentBFTKmer, uint32_t currentColor, uint32_t*& intersectingColors, BFT_kmer* endBFTKmer, string& path, uint32_t depth, uint32_t maxDepth);

    private:

        Graph* graph;

        Filter filter;

        BubbleStats* bubbleStats;
};

#endif // BUBBLE_BUILDER_H

