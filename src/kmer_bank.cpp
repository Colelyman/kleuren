/*
 * Implementation of kmer_bank.h
 */

#include "kmer_bank.h"

KmerBank::KmerBank(ifstream* fileStream) {
    kmerFile = fileStream;
}

string KmerBank::getNextKmer() {
    string nextKmer;

    *kmerFile >> nextKmer;

    return nextKmer;
}
