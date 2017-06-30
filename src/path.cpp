/*
 * Implementation of path.h
 */

#include <sstream>

#include "path.h"

using std::stringstream;

Path::Path(const Path& p) : color(p.color) {
    this->kmerLen = p.kmerLen;
}

Path::Path(const Color* color, size_t kmerLen) : color(color) {
    this->kmerLen = kmerLen;
}

string Path::getSequence() const {
    stringstream seq;
    for(size_t index : indexes) {
        seq << color->extractSubstring(index, kmerLen);
    }

    return seq.str();
}

void Path::addIndex(size_t idx) {
    indexes.push_back(idx);
}

void Path::append(string suffix) {
    seq << suffix;
}

int Path::getColorID() const {
    return color->getID();
}

int Path::runNW(Path path) const {
    string seqA = getSequence();
    string seqB = path.getSequence();

    /// @todo integrate the NW into this function
    
    return 0;
}
