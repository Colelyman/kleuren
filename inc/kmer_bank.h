/**
 * @class KmerBank
 *
 * KmerBank is the wrapper around how the kmers are stored. One could inherit from this class 
 * if one had a new way of storing kmers.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/22
 *
 */

#ifndef KMER_BANK_H
#define KMER_BANK_H

#include <string>
#include <fstream>
#include <set>
#include <iostream>

using std::string;
using std::ifstream;
using std::set;
using std::cerr;
using std::endl;

class KmerBank {

    public:
        KmerBank() { }

        KmerBank(ifstream* fileStream);

        ~KmerBank();

        /// Returns the next kmer in the file
        string getNextKmer();

    private:
        /// The pointer to the file handle to the file of kmers
        ifstream* kmerFile; 

        /// The current line in kmerFile that, which is also equal to the number of kmers
        /// that KmerBank has returned
        unsigned int lineNum;

        /// The kmer length found in kmerFile
        size_t kmerLen;

        /// A buffer for holding the next kmer
        char* buffer = NULL;

        /// The set of visited kmers
        set<string>* visited = NULL;
};

#endif // KMER_BANK_H
