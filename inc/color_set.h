/**
 * @class ColorSet
 *
 * ColorSet represents a set of colors, as well as various operations on the set.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/21
 *
 */

#ifndef COLOR_SET_H
#define COLOR_SET_H

#include <string>
#include <set>

#include "color.h"

using std::string;
using std::set;

class ColorSet {

    public:
        ColorSet(set<Color*> colors);

        /// Returns true if all of the colors contain the kmer
        bool allContainsKmer(string& kmer);

        /// Returns the number of colors that contain the kmer
        int numContainsKmer(string& kmer);

        /// Returns the subset of colors that contain the kmer
        ColorSet containsKmer(string& kmer);

        /// Returns the set of all colors
        set<Color*> getColors();

        /// Returns a begin iterator over the set of colors
        set<Color*>::iterator getBeginIterator();

        /// Returns an end iterator over the set of colors
        set<Color*>::iterator getEndIterator();

    private:
        /// The set of colors contained by this object
        set<Color*> colors;

};

#endif // COLOR_SET_H
