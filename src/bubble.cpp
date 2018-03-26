/*
 * Implementation of bubble.h
 */

#include <iostream>
#include <set>

#include "bubble.h"

using std::cout;
using std::endl;
using std::set;
using std::pair;

Bubble::Bubble() { }

bool Bubble::pathExists(Path pathCandidate) const {
    for(auto const& path : paths) {
        if(pathCandidate.getSequence() == path.getSequence()) {
            return true;
        }
    }
    return false;
}

bool Bubble::isValid(size_t kmerLen, uint32_t n) const {
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
    // make sure that all of the colors are accounted for, and that there are no paths
    // with duplicate colors
    set<string> colors;
    for(auto const& path : paths) {
        for(auto const& color : path.getColorNames()) {
            pair<set<string>::iterator, bool> result = colors.insert(color);
            // check if the color has been inserted
            if(!result.second) {
                return false;
            }
        }
    }

    if(colors.size() < n) {
        return false;
    }

    return true;
}

void Bubble::addPath(Path path) {
    // check if the sequence matches any other paths
    for(auto& p : paths) {
        if(p.getSequence() == path.getSequence()) {
            p.addColorNames(path.getColorNames());
            return;
        }
    }
    // no match, thus add the path to paths
	paths.push_back(path);
}

vector<Path> Bubble::getPaths() const {
    return paths;
}
