/*
 * Implementation of bubble.h
 */

#include "bubble.h"

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

bool Bubble::pathExists(Path path) const {
    return paths.find(path) != paths.end();
}

void Bubble::addPath(Path path, Color* color) {
    if(paths.find(path) == paths.end()) { // path is not found
        paths[path] = set<Color*>({color});
    }
    else { // path exists in paths, therefore add the color
        paths[path].insert(color);
    }
}

set<Color*> Bubble::getColors(Path path) const {
    if(pathExists(path)) {
        return paths.at(path);
    }
}

vector<string> Bubble::getColorNames(Path path) const {
    set<Color*> colors = getColors(path);
    vector<string> names;
    for(Color* color : colors) {
        names.push_back(color->getName());
    }
    return names;
}

vector<int> Bubble::getColorIDs(Path path) const {
    set<Color*> colors = getColors(path);
    vector<int> ids;
    for(Color* color : colors) {
        ids.push_back(color->getID());
    }
    return ids;
}

map<Path, set<Color*> > Bubble::getPaths() const {
    return paths;
}
