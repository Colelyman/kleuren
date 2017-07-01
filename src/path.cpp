/*
 * Implementation of path.h
 */

#include <sstream>

#include "path.h"

using std::stringstream;

Path::Path(const Path& p) : color(p.color) {
    this->kmerLen = p.kmerLen;
    this->seq << p.seq.rdbuf();
}

Path::Path(const Color* color, size_t kmerLen) : color(color) {
    this->kmerLen = kmerLen;
}

string Path::getSequence() const {
    return seq.str();
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
