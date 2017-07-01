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
#include <sstream>

#include "color.h"

using std::string;
using std::vector;
using std::stringstream;

class Path {

    public:
        Path(const Path& p);

        Path(const Color* color, size_t kmerLen);

        /// Returns the actual sequence of the path
        string getSequence() const;

        /// Appends to the seq
        void append(string suffix);

        /// Returns the ID of the Color that this path is associated with
        int getColorID() const;

        /** 
         * Runs the Needleman-Wunsch alignment algorithm to compare with another 
         * path.
         * @param path the path to compare to
         * @return the score, which shows how similar two paths are with each other
         */
        int runNW(Path path) const;

    private:
        /// The color that the path represents
        const Color* color;

        /**
         * seq is a stringstream that represents the sequence of the path. This is a 
         * stringstream because it makes the path easier to construct and get the sequence
         * from.
         */
        stringstream seq;

        size_t kmerLen;

};

#endif // PATH_H
