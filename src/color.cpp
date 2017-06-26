/*
 * Implementation of color.h.
 */

#include "color.h"

Color::Color(string name, string pathToFMIndex) {

}

Color::~Color() {

}

bool Color::isVertex(string& s) {
    return DBGQuery::isVertex(fmIndex, s);
}

bool Color::isPrefixNeighbor(string& s, char b) {
    return DBGQuery::isPrefixNeighbor(fmIndex, s, b);
}

bool Color::isSuffixNeighbor(string& s, char b) {
    return DBGQuery::isSuffixNeighbor(fmIndex, s, b);
}

string Color::getSuffixNeighbors(string& s) {
    return DBGQuery::getSuffixNeighbors(fmIndex, s);
}

string Color::getPrefixNeighbors(string& s) {
    return DBGQuery::getPrefixNeighbors(fmIndex, s);
}

pair<string, size_t> Color::extractSubstringAndIndex(size_t idx, size_t len) {
    return DBGQuery::extractSubstringAndIndex(fmIndex, idx, len);
}

string Color::extractSubstring(size_t idx, size_t len) {
    return DBGQuery::extractSubstring(fmIndex, idx, len);
}

string Color::getName() {
    return name;
}

int Color::getID() {
    return id;
}

FMIndex* Color::getFMIndex() {
    return fmIndex;
}
