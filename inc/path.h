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
#include <set>
#include <sstream>

#include "color.h"

using std::string;
using std::vector;
using std::set;
using std::stringstream;

class Path {

    public:
        Path(string initialSeq);

        Path(const Path& p);

        /// Returns the actual sequence of the path
        string getSequence() const;

        /// Appends to the seq
        void append(string suffix);

        /** 
         * Runs the Needleman-Wunsch alignment algorithm to compare with another 
         * path.
         * @param path the path to compare to
         * @return the score, which shows how similar two paths are with each other
         */
        int runNW(Path path) const;

        /**
         * Counts the number of shared kmers of length kmerLen with another
         * path.
         * @param path the path to compare to
         * @return the number of shared kmers
         */
        unsigned int runSharedKmerCount(Path path, unsigned int kmerLen) const;

        bool operator<(const Path& rhsPath) const {
            return this->getSequence() < rhsPath.getSequence();
        }

    private:
        /**
         * seq is a stringstream that represents the sequence of the path. This is a 
         * stringstream because it makes the path easier to construct and get the sequence
         * from.
         */
        stringstream seq;

};

#endif // PATH_H
