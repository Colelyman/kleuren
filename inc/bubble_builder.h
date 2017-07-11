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
        /// Returns the Bubble built starting at startKmer for colors
        Bubble build(string& startKmer, ColorSet colors, unsigned int maxDepth);

        /** 
         * Finds the index of the ending kmer, which is the next kmer 
         * that contains all of the colors.
         * @param startKmer the kmer to start searching for
         * @param color the Color to find the endKmer in
         * @param colors the ColorSet to check against
         * @return the next kmer that is present in all of the colors of the ColorSet, but
         * if there is no kmer that is present in all of the colors of the ColorSet the function
         * will return null
         */
        string findEndKmer(string& startKmer, const Color* color, const ColorSet colors);

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
        string extendPath(string startKmer, string endKmer, const Color* color, unsigned int maxDepth);
};

#endif // BUBBLE_BUILDER_H
        
