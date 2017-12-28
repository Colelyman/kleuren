/*
 * Implementation of bubble.h
 */

#include <iostream>

#include "bubble.h"

using std::cout;
using std::endl;

Bubble::Bubble() { }


bool Bubble::pathExists(Path path) const {
    return paths.find(path) != paths.end();
}

bool Bubble::isValid(size_t kmerLen) const {
    // check if there is more than one path
    if(paths.size() <= 1) {
        return false;
    }
    // check if any of the paths are empty or less than or equal to the kmer length
    for(auto const& path : paths) {
        if(path.first.getSequence().empty() || path.first.getSequence().length() <= kmerLen) {
            return false;
        }
    }

    return true;
}

void Bubble::addPath(Path path, bit_vector colors) {
	paths[path] = colors;
}

bit_vector Bubble::getColors(Path path) const {
    if(pathExists(path)) {
        return paths.at(path);
    }
}

map<Path, bit_vector> Bubble::getPaths() const {
    return paths;
}

vector<Path> Bubble::pathsToVector() const {
    vector<Path> pathVector;
    for(auto const& path : paths) {
        pathVector.push_back(path.first);
    }
    return pathVector;
}
