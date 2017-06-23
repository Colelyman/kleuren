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

        size_t getKmerLen();
        void setKmerLen(size_t len);

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

        /// The length of kmer to use when querying for nodes 
        size_t kmerLen;

};

#endif // ARGS_H
