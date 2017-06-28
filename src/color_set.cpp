/*
 * Implementation of color_set.h
 */

#include "color_set.h"

ColorSet::ColorSet(set<Color*> colors) {
    this->colors = colors;
}

bool ColorSet::allContainsKmer(string& kmer) {
    if(numContainsKmer(kmer) == colors.size()) {
        return true;
    }
    else {
        return false;
    }
}

int ColorSet::numContainsKmer(string& kmer) {
    return containsKmer(kmer).getColors().size();
}

ColorSet ColorSet::containsKmer(string& kmer) {
    set<Color*> subColors;

    for(Color* color : colors) {
        if(color->isVertex(kmer)) {
            subColors.insert(color);
        }
    }

    return ColorSet(subColors);
}

set<Color*> ColorSet::getColors() {
    return colors;
}

set<Color*>::iterator ColorSet::getBeginIterator() {
    return colors.begin();
}

set<Color*>::iterator ColorSet::getEndIterator() {
    return colors.end();
}
