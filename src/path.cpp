/*
 * Implementation of path.h
 */

#include <sstream>

#include "path.h"

using std::stringstream;

Path::Path(const Path& p) {//: color(p.color) {
    this->colors = p.colors;
    this->seq << p.seq.rdbuf();
}

Path::Path(Color* color) {
    colors.push_back(color);
}

string Path::getSequence() const {
    return seq.str();
}

void Path::append(string suffix) {
    seq << suffix;
}

vector<int> Path::getColorIDs() const {
    vector<int> ids;
    for(auto const& color : colors) {
        ids.push_back(color->getID());
    }
    return ids;
}

vector<string> Path::getColorNames() const {
    vector<string> names;
    for(auto const& color : colors) {
        names.push_back(color->getName());
    }
    return names;
}

int Path::runNW(Path path) const {
    string seqA = getSequence();
    string seqB = path.getSequence();

    /// @todo integrate the NW into this function
    
    return 0;
}
