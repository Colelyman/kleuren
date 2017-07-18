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

        string getColorsFilePath();
        void setColorsFilePath(string path);

        string getKmerFilePath();
        void setKmerFilePath(string path);

        string getBubbleFilePath();
        void setBubbleFilePath(string path);

        unsigned int getN();
        void setN(unsigned int n);

    private:
        /**
         * The path to the file that specifies the colors.
         * The formatting of this file should be as follows:
         * 
         *      <path to color1 bwtdisk file> <name of color1>
         *      <path to color2 bwtdisk file> <name of color2>
         *      <path to color3 bwtdisk file> <name of color3>
         *      ...
         *
         * Replace the <...> with the appropriate text. Here is an explicit example:
         *
         *      /home/cole/homo_sapiens.bwtdisk Homo_sapiens
         *      /home/cole/mus_musculus.bwtdisk Mus_musculus
         *
         * which has two colors, one representing a human and another representing a mouse.
         */
        string colorsFilePath;

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
         *      > bubble 1 <color1 name>
         *      ACTGT ...
         *      > bubble 1 <color2 name>
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
        unsigned int n;

};

#endif // ARGS_H
