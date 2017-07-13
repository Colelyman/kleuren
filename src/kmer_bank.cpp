/*
 * Implementation of kmer_bank.h
 */

#include "kmer_bank.h"

KmerBank::KmerBank(ifstream* fileStream) {
    kmerFile = fileStream;
    lineNum = 0;
    string firstKmer;
    // get the first kmer of the file
    getline(*kmerFile, firstKmer);
    // set the kmerLen
    kmerLen = firstKmer.length();
    // return to read the first line of the file again
    kmerFile->seekg(0, kmerFile->beg);
    visited = new set<string>();
}

KmerBank::~KmerBank() {
    delete visited;
}

string KmerBank::getNextKmer() {
    
}
