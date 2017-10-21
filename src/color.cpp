/*
 * Implementation of color.h.
 */

#include "color.h"

Color::Color(int id, string name, string pathToFMIndex) {
    this->id = id;
    this->name = name;
    fmIndex = new FMIndex(pathToFMIndex, 256);
}

Color::Color(int id, int numColors, string name, string pathToFMIndex) {
    this->id = id;
    this->name = name;
    this->bitVector = bit_vector(numColors, 0);
    bitVector[id] = 1;
    fmIndex = new FMIndex(pathToFMIndex, 256);
}

Color::~Color() {
    delete fmIndex;
}

bool Color::isVertex(string& s) const {
    return DBGQuery::isVertex(fmIndex, s);
}

bool Color::isPrefixNeighbor(string& s, char b) const {
    return DBGQuery::isPrefixNeighbor(fmIndex, s, b);
}

bool Color::isSuffixNeighbor(string& s, char b) const {
    return DBGQuery::isSuffixNeighbor(fmIndex, s, b);
}

vector<string> Color::getSuffixNeighbors(string s) const {
    vector<string> neighbors;
    string neighborBases = DBGQuery::getSuffixNeighbors(fmIndex, s);
    string suffix = s.substr(1);

    for(unsigned int i = 0; i < neighborBases.length(); i++) {
        string neighbor = suffix + neighborBases[i];
        neighbors.push_back(neighbor);
    }

    return neighbors;
}

vector<string> Color::getPrefixNeighbors(string& s) const {
    vector<string> neighbors;
    string neighborBases = DBGQuery::getPrefixNeighbors(fmIndex, s);
    string prefix = s.substr(0, s.length() - 1);

    for(unsigned int i = 0; i < neighborBases.length(); i++) {
        string neighbor = neighborBases[i] + prefix;
        neighbors.push_back(neighbor);
    }

    return neighbors;
}

bool Color::hasSuffixNeighbors(string& s) const {
    if(DBGQuery::getSuffixNeighbors(fmIndex, s).length() == 0) {
        return false;
    }
    else {
        return true;
    }
}

bool Color::hasPrefixNeighbors(string& s) const {
    if(DBGQuery::getPrefixNeighbors(fmIndex, s).length() == 0) {
        return false;
    }
    else {
        return true;
    }
}

pair<string, size_t> Color::extractSubstringAndIndex(size_t idx, size_t len) const {
    return DBGQuery::extractSubstringAndIndex(fmIndex, idx, len);
}

string Color::extractSubstring(size_t idx, size_t len) const {
    return DBGQuery::extractSubstring(fmIndex, idx, len);
}

string Color::getName() const {
    return name;
}

int Color::getID() const {
    return id;
}

FMIndex* Color::getFMIndex() const {
    return fmIndex;
}
