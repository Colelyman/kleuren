/**
 * @class Args
 *
 * This is a data object that contains all of the arguments for kleuren.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/22
 *
 */

#ifndef ARGS_H
#define ARGS_H

#include <string>

using std::string;

class Args {
    
    public:
        /// Returns a string representation of the arguments provided
        string toString();

        string getBFTFilePath();
        void setBFTFilePath(string path);

        string getKmerFilePath();
        void setKmerFilePath(string path);

        string getBubbleFilePath();
        void setBubbleFilePath(string path);

        uint32_t getN();
        void setN(uint32_t n);

        uint32_t getMaxDepth();
        void setMaxDepth(uint32_t maxDepth);

        uint32_t getKmerLen();
        void setKmerLen(uint32_t kmerLen);

    private:
        /**
         * The path to the file that is generated by BloomFilterTrie.
         * This is used to represent the Colored de Bruijn Graph because
         * it provides fast kmer lookups.
         */
        string bftFilePath;

        /**
         * The path to the file that contains the super set of all of the kmers from
         * each of the colors.
         * The formatting of the file should be as follows:
         *      
         *      <kmer> <number of occurances of the kmer>
         *      ...
         *
         * One can use any kmer counting software as long as it can output a file in the
         * above format. The kmer counting software DSK is provided and recommended.
         */
        string kmerFilePath;

        /**
         * The path to the file that will be created that will hold the bubbles in FASTA format.
         * The outputted file will look something like this:
         *
         *      > bubble 1 <color1 name>, <color2 name>
         *      ACTGT ...
         *      > bubble 1 <color3 name>
         *      ACTGG ...
         *      ...
         *      > bubble 1 <colorn name>
         *      ...
         *      > bubble n <colorn name>
         */
        string bubbleFilePath;

        /**
         * The number of colors necessary in order to start a bubble formation. This parameter
         * is checked in the method ColorSet::nContainsKmer(). In essence, the higher the value
         * of n is, the less bubbles will be found, and the faster kleuren will run; and vice versa.
         */
        uint32_t n;

        /**
         * The maximum depth to recurse when extending the path to build the bubbles. The 
         * larger the maxDepth the more paths the recursive function will explore, thereby
         * the longer kleuren will take and the more bubbles it will find.
         */
        uint32_t maxDepth;

        /// The size of kmer to use to construct the Colored de Bruijn Graph.
        uint32_t kmerLen;

};

#endif // ARGS_H
