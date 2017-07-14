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
    // set the kmerLen as the length of the firstKmer + 1 to account for \n
    kmerLen = firstKmer.length() + 1;
    // return to read the first line of the file again
    kmerFile->seekg(0, kmerFile->beg);

    buffer = new char[kmerLen];
    visited = new set<string>();
}

KmerBank::~KmerBank() {
    delete[] buffer;
    delete visited;
}

string KmerBank::getNextKmer() {
    // move the cursor to the next line, with the next kmer
    kmerFile->seekg(lineNum * kmerLen);
    // check if the end of file is reached or an error has occurred
    if((kmerFile->rdstate() & std::ifstream::eofbit) != 0 ||
            (kmerFile->rdstate() & std::ifstream::failbit) != 0) {
        return "";
    }
    kmerFile->read(buffer, kmerLen - 1);
    string nextKmer = string(buffer);
    lineNum++;

    // add the kmer to visited
    visited->insert(nextKmer);

    return nextKmer;
}
