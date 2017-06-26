/**
 * @class Path
 *
 * Path is a class that represents the path that a specific color takes through 
 * a Bubble. It is used heavily in the comparison between colors.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/21
 *
 */

#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>

#include "color.h"

using std::string;
using std::vector;

class Path {

    public:
        Path();

        /// Returns the actual sequence of the path
        string getSequence();

        /** 
         * Runs the Needleman-Wunsch alignment algorithm to compare with another 
         * path.
         * @param path the path to compare to
         * @return the score, which shows how similar two paths are with each other
         */
        int runNW(Path path);

    private:
        /// The color that the path represents
        Color* color;

        /// @todo figure out the best way to represent the sequence of indexes...
        vector<size_t> indexes;

        size_t kmerSize;

};

#endif // PATH_H
