/*
 * Implementation of args.h
 */

#include "args.h"

string Args::toString() {
    return "";
}

string Args::getBFTFilePath() {
    return bftFilePath;
}

void Args::setBFTFilePath(string path) {
    bftFilePath = path;
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

uint32_t Args::getN() {
    return n;
}

void Args::setN(uint32_t n) {
    this->n = n;
}

uint32_t Args::getMaxDepth() {
    return maxDepth;
}

void Args::setMaxDepth(uint32_t maxDepth) {
    this->maxDepth = maxDepth;
}

