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

string Args::getKmerFilePath() {
    return kmerFilePath;
}

void Args::setKmerFilePath(string path) {
    kmerFilePath = path;
}

string Args::getBubbleFilePath() {
    return bubbleFilePath;
}

void Args::setBubbleFilePath(string path) {
    bubbleFilePath = path;
}

unsigned int Args::getN() {
    return n;
}

void Args::setN(unsigned int n) {
    this->n = n;
}
