/*
 * Implementation of bubble.h
 */

#include "bubble.h"

#define DEBUG(STR) if(true) printf("In file: %s on line: %d\n\tMessage: %s\n", __FILE__, __LINE__, STR);

Bubble::Bubble() { }

bool Bubble::pathExists(string path) const {
    if(paths.find(path) != paths.end()) {
        return true;
    }
    return false;
}

bool Bubble::isValid(size_t kmerLen, uint32_t n) const {
    // check if there is more than one path
    if(paths.size() <= 1) {
        DEBUG("There are 1 or less paths")
        return false;
    }
    // check if any of the paths are empty or less than or equal to the kmer length
    for(auto const& path : paths) {
        if(path.first.empty() || path.first.length() <= kmerLen) {
            DEBUG("A path length is less than the kmer length")
            return false;
        }
    }
    // make sure that all of the colors are accounted for, and that there are no paths
    // with duplicate colors
    set<uint32_t> colors;
    for(auto const& path : paths) {
        for(auto const& color : path.second) {
            pair<set<uint32_t>::iterator, bool> result = colors.insert(color);
            // check if the color has been inserted
            if(!result.second) {
                DEBUG("There is a duplicate color somewhere")
                return false;
            }
        }
    }

    if(colors.size() < n) {
        DEBUG("There aren't enough colors")
        return false;
    }

    return true;
}

set<uint32_t> colorArrayToSet(uint32_t* colors) {
    set<uint32_t> newColorSet;
    for(uint32_t i = 1; i <= colors[0]; i++) {
        newColorSet.insert(colors[i]);
    }
    return newColorSet;
}

void Bubble::addPath(string path, uint32_t* colors) {
    auto p = paths.find(path);
    if(p != paths.end()) {
        auto colorSet = colorArrayToSet(colors);
        p->second.insert(colorSet.begin(), colorSet.end());
    }
    else {
        paths[path] = colorArrayToSet(colors);
    }
}

map<string, set<uint32_t> > Bubble::getPaths() const {
    return paths;
}
