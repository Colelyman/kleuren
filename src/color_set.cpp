/*
 * Implementation of color_set.h
 */

#include "color_set.h"

ColorSet::ColorSet(set<Color*> colors) {
    this->colors = colors;
}

bool ColorSet::allContainsKmer(string& kmer) const {
    if(numContainsKmer(kmer) == colors.size()) {
        return true;
    }
    else {
        return false;
    }
}

size_t ColorSet::numContainsKmer(string& kmer) const {
    return containsKmer(kmer).getColors().size();
}

ColorSet ColorSet::containsKmer(string& kmer) const {
    set<Color*> subColors;

    for(Color* color : colors) {
        if(color->isVertex(kmer)) {
            subColors.insert(color);
        }
    }

    return ColorSet(subColors);
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
