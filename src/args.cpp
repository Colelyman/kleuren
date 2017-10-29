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

string Args::getMatrixFilePath() {
    return matrixFilePath;
}

void Args::setMatrixFilePath(string path) {
    matrixFilePath = path;
}

unsigned int Args::getN() {
    return n;
}

void Args::setN(unsigned int n) {
    this->n = n;
}

unsigned int Args::getMaxDepth() {
    return maxDepth;
}

void Args::setMaxDepth(unsigned int maxDepth) {
    this->maxDepth = maxDepth;
}

unsigned int Args::getKmerLen() {
    return kmerLen;
}

void Args::setKmerLen(unsigned int kmerLen) {
    this->kmerLen = kmerLen;
}
