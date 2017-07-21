/*
 * Implementation of path.h
 */

#include "path.h"

Path::Path(const Path& p) {
    this->seq << p.seq.rdbuf();
}

string Path::getSequence() const {
    return seq.str();
}

void Path::append(string suffix) {
    seq << suffix;
}

int Path::runNW(Path path) const {
    string seqA = getSequence();
    string seqB = path.getSequence();

    /// @todo integrate the NW into this function
    
    return 0;
}

/// @todo this doesn't need to account for reverse complement does it?
unsigned int Path::runSharedKmerCount(Path path, unsigned int kmerLen) const {
    string seqA = getSequence();
    string seqB = path.getSequence();

    if(seqA.length() == 0 || seqB.length() == 0) {
        return 0;
    }

    unsigned int count = 0;
    string kmer;
    for(unsigned int i = 0; i < seqA.length() - kmerLen + 1; i++) {
        kmer = seqA.substr(i, kmerLen);
        if(seqB.find(kmer) != string::npos) {
            count++;
        }
    }

    return count;
}
