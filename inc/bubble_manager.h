/**
 * @class BubbleManager
 *
 * BubbleManager manges the bubbles, in the sense that it controls what operations are 
 * performed on the bubbles after they are constructed by the BubbleBuilder.
 *
 * @author Cole Lyman
 *
 * @date 2017/7/14
 *
 */

#ifndef BUBBLE_MANAGER
#define BUBBLE_MANAGER

#include <fstream>
#include <map>
#include <utility>
#include <vector>

#include "bubble.h"
#include "graph.h"

using std::ofstream;
using std::endl;
using std::map;
using std::pair;
using std::vector;

class BubbleManager {

    public:
        BubbleManager() { }

        BubbleManager(ofstream* bubbleFile, Graph* graph);

        vector<string> getColorNames(set<uint32_t> colors);

        /// Write the various paths of the bubble to a file in FASTA format
        void writeBubble(Bubble bubble);

        /// Count the number of shared kmers in the bubble and add it to the matrix
        void countSharedKmers(Bubble bubble, uint32_t kmerLen);

        /// Averages the sharedKmerMatrix so that the values are normalized
        /// @return the sharedKmerMatrix normalized
        map<int, map<int, float> > averageSharedKmerMatrix();

    private:
        /// The pointer to the file handle in which the bubbles will be written to
        ofstream* bubbleFile;

        Graph* graph;

        /**
         * The matrix showing the similarity between colors based on shared kmers.
         * The key is a pair of ints that represent the color's ID, and the value is
         * also a pair, but of uint32_t's representing the number of shared kmers
         * between the two colors, and the number of bubbles the colors are found in.
         *
         * The number of bubbles that the colors are found in are kept so that the
         * average number of shared kmers can more accurately be calculated.
         */
        map<pair<int, int>, pair<uint32_t, uint32_t> > sharedKmerMatrix;

        /// The number of bubbles that have been processed
        uint32_t n;

};

#endif // BUBBLE_MANAGER
