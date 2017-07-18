/*
 * Implementation of color_set.h
 */

#include "color_set.h"

ColorSet::ColorSet(set<Color*> colors, unsigned int n) {
    this->colors = colors;
    this->n = n;
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

/// @todo determine if this method should be deleted...
ColorSet ColorSet::containsKmer(string& kmer) const {
    set<Color*> subColors;

    for(Color* color : colors) {
        if(color->isVertex(kmer)) {
            subColors.insert(color);
        }
    }

    /// @todo figure out where to get n from...
    return ColorSet(subColors, 0);
}

set<Color*> ColorSet::getColors() const {
    return colors;
}

set<Color*>::iterator ColorSet::getBeginIterator() const {
    return colors.begin();
}

set<Color*>::iterator ColorSet::getEndIterator() const {
    return colors.end();
}
