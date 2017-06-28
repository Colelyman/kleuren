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
        Path(Color* color);

        /// Returns the actual sequence of the path
        string getSequence();

        /// Adds an index to the path
        void addIndex(size_t idx);

        /// Returns the ID of the Color that this path is associated with
        int getColorID();

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

        /**
         * indexes is how the sequence of the path is stored in an efficient manner.
         * Each element in indexes is an index corresponding to the color such that the
         * sequence of the path can be constructed by concatenating the substring at each
         * index, where each substring is of length kmerLen.
         */
        /// @todo figure out the best way to represent the sequence of indexes...
        vector<size_t> indexes;

        size_t kmerLen;

};

#endif // PATH_H
