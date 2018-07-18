/**
 * @class BubbleStats
 *
 * This is a data object that will contain various statistics about the bubbles.
 * More specifically this class will detail the attributes about the CdBG that
 * is being traversed.
 *
 * @author Cole Lyman
 *
 * @date 2018/7/10
 * 
 */

#ifndef BUBBLE_STATS_H_
#define BUBBLE_STATS_H_

#include <sstream>
#include <stdint.h>
#include <map>

using std::stringstream;
using std::string;
using std::map;

class BubbleStats {

    public:
        BubbleStats();
        
        /// Return the values of data members in a pretty string
        string toString();

        /// Increments the numVisitedNodes
        /// @return the new value of numVisitedNodes
        uint32_t incNumVisitedNodes(uint32_t num = 1);
        
        /// Increments the numKmers
        /// @return the new value of numKmers
        uint32_t incNumKmers(uint32_t num = 1);

        /// Increments the number of bubbles in which no end kmer was found
        /// @return the new value of numNoEndKmersFound
        uint32_t incNumNoEndKmersFound(uint32_t num = 1);

        /// Increments the number of bubbles in which no paths were found
        /// @return the new value of numNoPathsFound
        uint32_t incNumNoPathsFound(uint32_t num = 1);

        /// Increments the number of valid bubbles found
        /// @return the new value of numBubblesFound
        uint32_t incNumBubblesFound(uint32_t num = 1);

        /// Increments the value of numColorsInNodes[color]
        /// @return the value of numColorsInNodes[color]
        uint32_t incNumColorsInNodes(uint32_t color, uint32_t num = 1);

    private:
        /// The number of nodes that kleuren has visited.
        uint32_t numVisitedNodes;

        /// The number of kmers that kleuren has tested.
        uint32_t numKmers;

        /// The number of bubbles in which there was no end kmer found
        uint32_t numNoEndKmersFound;

        /// The number of bubbles in which there are no paths
        uint32_t numNoPathsFound;

        /// The number of bubbles found 
        uint32_t numBubblesFound;

        /// A map that contains how many colors are present in the nodes
        map<uint32_t, uint32_t> numColorsInNodes;
};

#endif // BUBBLE_STATS_H_
