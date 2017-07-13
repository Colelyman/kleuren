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
#include <set>

using std::string;
using std::set;

class KmerBank {

    public:
        KmerBank() { }

        KmerBank(string path);

        ~KmerBank();

        /// Returns a random kmer that has not been returned yet
        string getRandomKmer();

        /// Returns an iterator over the kmers
        /// @todo figure out what to return here...
        void getIterator();

    private:
        /// The path to where the kmers are stored
        string kmerFilePath; 

        /// The set of visited kmers
        set<string>* visited;
};

#endif // KMER_BANK_H
