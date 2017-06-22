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

#include "bubble.h"
#include "color.h"
#include "color_set.h"
#include "path.h"

using std::string;

class BubbleBuilder {

    public:
        /// Returns the Bubble built starting at kmer for colors
        Bubble build(string& kmer, ColorSet colors);

    private:
        /** 
         * Finds the ending kmer, which is the next kmer that contains all of the colors.
         * @param startKmer the kmer to start searching for
         * @param color the Color to find the endKmer in
         * @param colors the ColorSet to check against
         * @return the next kmer that is present in all of the colors of the ColorSet
         */
        string& findEndKmer(string& startKmer, Color color, ColorSet colors);

        /**
         * Extends the path between startKmer and endKmer for a given color.
         * @param startKmer the kmer to start the path with
         * @param endKmer the kmer to finish the path with
         * @param color the Color to use to extend the path
         * @return the path for color between startKmer and endKmer
         */
        Path extendPath(string& startKmer, string& endKmer, Color color);

};

#endif // BUBBLE_BUILDER_H
        
