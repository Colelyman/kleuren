/*
 * Implementation of bubble.h
 */

#include <iostream>

#include "bubble.h"

using std::cout;
using std::endl;

Bubble::Bubble() { }

bool Bubble::pathExists(Path pathCandidate) const {
    for(auto const& path : paths) {
        if(pathCandidate.getSequence() == path.getSequence()) {
            return true;
        }
    }
    return false;
}

bool Bubble::isValid(size_t kmerLen) const {
    // check if there is more than one path
    if(paths.size() <= 1) {
        return false;
    }
    // check if any of the paths are empty or less than or equal to the kmer length
    for(auto const& path : paths) {
        if(path.getSequence().empty() || path.getSequence().length() <= kmerLen) {
            return false;
        }
    }

    return true;
}

void Bubble::addPath(Path path) {
	paths.push_back(path);
}

vector<Path> Bubble::getPaths() const {
    return paths;
}
