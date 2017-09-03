/*
 * Implementation of kmer_bank.h
 */

#include "kmer_bank.h"

KmerBank::KmerBank(ifstream* fileStream) {
    kmerFile = fileStream;
    visited = shared_ptr<set<string> >(new set<string>());
}

string KmerBank::getNextKmer() {
    string nextKmer;

    *kmerFile >> nextKmer;

    // add the kmer to visited
    visited->insert(nextKmer);

    return nextKmer;
}
