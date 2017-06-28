/*
 * Implementation of path.h
 */

#include <stringstream>

#include "path.h"

using std::stringstream;

Path::Path(Color* color, size_t kmerLen) {
    this->color = color;
    this->kmerLen = kmerLen;
}

string Path::getSequence() {
    stringstream seq;
    for(size_t index : indexes) {
        seq << color->extractSubstring(index, kmerLen);
    }

    return seq.str();
}

void Path::addIndex(size_t idx) {
    indexes.push_back(idx);
}

int Path::getColorID() {
    return color->getID();
}

int Path::runNW(Path path) {
    string seqA = getSequence();
    string seqB = path.getSequence();

    /// @todo integrate the NW into this function
}
