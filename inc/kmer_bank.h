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

using std::string;

class KmerBank {

    public:
        KmerBank();

        /// Returns a random kmer 
        string getRandomKmer();

        /// Returns an iterator over the kmers
        /// @todo figure out what to return here...
        void getIterator();

    private:
        /// @todo figure out what data members are needed for this
    
};

#endif // KMER_BANK_H
