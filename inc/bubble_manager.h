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

#include "bubble.h"

using std::ofstream;
using std::endl;

class BubbleManager {

    public:
        BubbleManager() { }

        BubbleManager(ofstream* file);

        /// Write the various paths of the bubble to a file in FASTA format
        void writeBubble(Bubble bubble);

    private:
        /// The pointer to the file handle in which the bubbles will be written to
        ofstream* bubbleFile;

        /// The number of bubbles that have been processed
        unsigned int n;

};

#endif // BUBBLE_MANAGER
