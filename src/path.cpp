/*
 * Implementation of path.h
 */
#include <iostream>

#include "path.h"

using std::cout;
using std::endl;

Path::Path(string initialSeq) {
    seq = initialSeq;
}

/*Path::Path(const Path& p) {
    cout << "\t\tp.seq.str(): " << p.seq.str() << endl;
    this->seq << p.seq.rdbuf();
    cout << "\t\tthis.str():  " << this->seq.str() << endl;
}*/

string Path::getSequence() const {
    return seq;
}

void Path::append(string suffix) {
    seq += suffix;
}

void Path::addColorName(string colorName) {
    colorNames.push_back(colorName);
}

vector<string> Path::getColorNames() const {
    return colorNames;
}

int Path::runNW(Path path) const {
    string seqA = getSequence();
    string seqB = path.getSequence();

    /// @todo integrate the NW into this function
    
    return 0;
}

/// @todo this doesn't need to account for reverse complement does it?
uint32_t Path::runSharedKmerCount(Path path, uint32_t kmerLen) const {
    string seqA = getSequence();
    string seqB = path.getSequence();

    if(seqA.length() == 0 || seqB.length() == 0) {
        return 0;
    }

    uint32_t count = 0;
    string kmer;
    for(uint32_t i = 0; i < seqA.length() - kmerLen + 1; i++) {
        kmer = seqA.substr(i, kmerLen);
        if(seqB.find(kmer) != string::npos) {
            count++;
        }
    }

    return count;
}
