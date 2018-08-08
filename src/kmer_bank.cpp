/*
 * Implementation of kmer_bank.h
 */

#include "kmer_bank.h"

KmerBank::KmerBank(ifstream* fileStream) {
    kmerFile = fileStream;
    string temp;
    // consume first kmer
    *kmerFile >> temp;
    // consume next kmer or count
    *kmerFile >> temp;
    // check if first character of temp is a digit
    if(isdigit(temp[0])) {
        counts = true;
    }
    else {
        counts = false;
    }
    // rewind the filestream
    kmerFile->seekg(0);
}

string KmerBank::getNextKmer() {
    string nextKmer;
    int count;

    *kmerFile >> nextKmer;
    if(counts) {
        *kmerFile >> count;
    }

    return nextKmer;
}
