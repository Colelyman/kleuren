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
        /// This constructor sets ColorSet::n to be the size of the colors
        ColorSet(set<Color*> colors);

        ColorSet(set<Color*> colors, unsigned int n);

        /// Returns true if all of the colors contain the kmer
        bool allContainsKmer(string& kmer) const;

        /// Returns true if n or more of the colors contain the kmer
        bool nContainsKmer(string& kmer) const;

        /// Returns the number of colors that contain the kmer
        int numContainsKmer(string& kmer) const;

        /// Returns whether or not a color in colors has a prefix neighbor for kmer
        bool hasPrefixNeighbors(string& kmer) const;

        /// Returns whether or not a color in colors has a suffix neighbror for kmer
        bool hasSuffixNeighbors(string& kmer) const;

        /// Returns the subset of colors that contain the kmer
        ColorSet containsKmer(string& kmer) const;

        /// Returns the set of all colors
        set<Color*> getColors() const;

        /// Returns a begin iterator over the set of colors
        set<Color*>::iterator getBeginIterator() const;

        /// Returns an end iterator over the set of colors
        set<Color*>::iterator getEndIterator() const;

    private:
        /// The set of colors contained by this object
        set<Color*> colors;

        /// The number of colors needed to consider a building a bubble
        unsigned int n;
};

#endif // COLOR_SET_H
