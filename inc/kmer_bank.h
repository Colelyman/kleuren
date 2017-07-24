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
#include <memory>

using std::string;
using std::ifstream;
using std::set;
using std::shared_ptr;

class KmerBank {

    public:
        KmerBank() { }

        KmerBank(ifstream* fileStream);

        /// Returns the next kmer in the file
        string getNextKmer();

    private:
        /// The pointer to the file handle to the file of kmers
        ifstream* kmerFile; 

        /// The set of visited kmers
        shared_ptr<set<string> > visited;
};

#endif // KMER_BANK_H
