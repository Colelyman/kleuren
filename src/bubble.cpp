/*
 * Implementation of bubble.h
 */

#include <iostream>

#include "bubble.h"

using std::cout;
using std::endl;

Bubble::Bubble() {

}

map<pair<int, int>, int> Bubble::runNW() {
    map<pair<int, int>, int> results;
    // iterate over each pair of paths in this->paths
    /// @todo refactor runNW in Bubble
    /*for(unsigned int i = 0; i < paths.size() - 1; i++) {
        for(unsigned int j = i + 1; j < paths.size(); j++) {
            pair<int, int> currentPair;
            currentPair.first = paths[i].getColorID();
            currentPair.second = paths[j].getColorID();

            int score = paths[i].runNW(paths[j]);

            results[currentPair] = score;
        }
    }*/

    return results;
}

map<pair<int, int>, unsigned int> Bubble::runSharedKmerCount(unsigned int kmerLen) {
    // put the paths from the map into a vector
    vector<Path> pathVector = pathsToVector();
    map<pair<int, int>, unsigned int> results;
    // iterate over each pair of paths
    for(unsigned int i = 0; i < pathVector.size() - 1; i++) {
        for(unsigned int j = i + 1; j < pathVector.size(); j++) {
            unsigned int score = pathVector[i].runSharedKmerCount(pathVector[j], kmerLen);
            set<shared_ptr<Color> > iColors = paths[pathVector[i]];
            set<shared_ptr<Color> > jColors = paths[pathVector[j]];
            // get the pairs of colors
            for(auto const& iColor : iColors) {
                for(auto const& jColor : jColors) {
                    pair<int, int> currentPair = pair<int, int>(iColor->getID(), jColor->getID());

                    results[currentPair] = score;
                }
            }
        }
    }

    return results;
}

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

void Bubble::addPath(Path path, shared_ptr<Color> color) {
    //cout << "Bubble::addPath, seq: " << path.getSequence() << endl;
    if(paths.find(path) == paths.end()) { // path is not found
        paths[path] = set<shared_ptr<Color> >({color});
    }
    else { // path exists in paths, therefore add the color
        paths[path].insert(color);
    }
}

set<shared_ptr<Color> > Bubble::getColors(Path path) const {
    if(pathExists(path)) {
        return paths.at(path);
    }
}

vector<string> Bubble::getColorNames(Path path) const {
    set<shared_ptr<Color> > colors = getColors(path);
    vector<string> names;
    for(auto const& color : colors) {
        names.push_back(color->getName());
    }
    return names;
}

vector<int> Bubble::getColorIDs(Path path) const {
    set<shared_ptr<Color> > colors = getColors(path);
    vector<int> ids;
    for(auto const& color : colors) {
        ids.push_back(color->getID());
    }
    return ids;
}

map<Path, set<shared_ptr<Color> > > Bubble::getPaths() const {
    return paths;
}

vector<Path> Bubble::pathsToVector() const {
    vector<Path> pathVector;
    for(auto const& path : paths) {
        pathVector.push_back(path.first);
    }
    return pathVector;
}
