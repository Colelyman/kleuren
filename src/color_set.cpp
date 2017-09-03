/*
 * Implementation of color_set.h
 */

#include "color_set.h"

ColorSet::ColorSet(set<shared_ptr<Color> > colors) {
    this->colors = colors;
    this->n = colors.size();
}

ColorSet::ColorSet(set<shared_ptr<Color> > colors, unsigned int n) {
    this->colors = colors;
    if(n > 0) {
        this->n = n;
    }
    else if(n == 0) { // an n of 0 indicates to n to be set to the size of colors
        this->n = colors.size();
    }
}

bool ColorSet::allContainsKmer(string& kmer) const {
    if(numContainsKmer(kmer) == colors.size()) {
        return true;
    }
    else {
        return false;
    }
}

bool ColorSet::nContainsKmer(string& kmer) const {
    if(numContainsKmer(kmer) >= n) {
        return true;
    }
    else {
        return false;
    }
}

int ColorSet::numContainsKmer(string& kmer) const {
    return containsKmer(kmer).getColors().size();
}

bool ColorSet::hasPrefixNeighbors(string& kmer) const {
    for(auto const& color : colors) {
        if(color->hasPrefixNeighbors(kmer)) {
            return true;
        }
    }
    return false;
}
bool ColorSet::hasSuffixNeighbors(string& kmer) const {
    for(auto const& color : colors) {
        if(color->hasSuffixNeighbors(kmer)) {
            return true;
        }
    }
    return false;
}

/// @todo determine if this method should be deleted...
ColorSet ColorSet::containsKmer(string& kmer) const {
    set<shared_ptr<Color> > subColors;

    for(auto const& color : colors) {
        if(color->isVertex(kmer)) {
            subColors.insert(color);
        }
    }

    /// @todo figure out where to get n from...
    return ColorSet(subColors, 0);
}

set<shared_ptr<Color> > ColorSet::getColors() const {
    return colors;
}

set<shared_ptr<Color> >::iterator ColorSet::getBeginIterator() const {
    return colors.begin();
}

set<shared_ptr<Color> >::iterator ColorSet::getEndIterator() const {
    return colors.end();
}
