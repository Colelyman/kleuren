/*
 * Implementation of kmer_bank.h
 */

#include "kmer_bank.h"

KmerBank::KmerBank(string path) {
    kmerFilePath = path;
    visited = new set<string>();
}

KmerBank::~KmerBank() {
    delete visited;
}

string KmerBank::getRandomKmer() {

}

void KmerBank::getIterator() {

}
