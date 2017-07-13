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

using std::string;
using std::ifstream;
using std::set;

class KmerBank {

    public:
        KmerBank() { }

        KmerBank(ifstream* fileStream);

        ~KmerBank();

        /// Returns the next kmer in the file
        string getNextKmer();

    private:
        /// The file handle to the file of kmers
        ifstream* kmerFile; 

        /// The current line in kmerFile that, which is also equal to the number of kmers
        /// that KmerBank has returned
        unsigned int lineNum;

        /// The kmer length found in kmerFile
        size_t kmerLen;

        /// The set of visited kmers
        set<string>* visited;
};

#endif // KMER_BANK_H
