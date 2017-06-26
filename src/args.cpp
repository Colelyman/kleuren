/*
 * Implementation of args.h
 */

#include "args.h"

string Args::toString() {
    return "";
}

string Args::getColorsFilePath() {
    return colorsFilePath;
}

void Args::setColorsFilePath(string path) {
    colorsFilePath = path;
}

size_t Args::getKmerLen() {
    return kmerLen;
}

void Args::setKmerLen(size_t len) {
    kmerLen = len;
}
