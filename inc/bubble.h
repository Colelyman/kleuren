/**
 * @class Bubble
 *
 * Bubble represents a set of paths for 2 or more colors that share a common
 * starting and ending node.
 *
 * @author Cole Lyman
 *
 * @date 2018/5/21
 *
 */

#ifndef BUBBLE_H
#define BUBBLE_H

#include <map>
#include <string>
#include <set>
#include <utility>

using std::map;
using std::string;
using std::set;
using std::pair;

class Bubble {

    public:
        Bubble();

        /// Checks if the path is present in the bubble
        bool pathExists(string path) const;

        /**
         * Checks if a bubble is valid, meaning it fits the following criteria:
         *  - there is more than one path
         *  - none of the paths are empty
         *  - at least n colors are present in the bubble
         *  - there are no paths that have overlapping colors
         */
        bool isValid(size_t kmerLen, uint32_t n) const;

        /**
         * Adds a path to paths, and appends the color to the corresponding path
         * if the path is already contained in colors.
         * @param path the path to add to paths
         * @param colors the colors that are associated with that path
         */
        void addPath(string path, uint32_t* colors);

        /// Returns the paths of the bubble
        map<string, set<uint32_t> > getPaths() const;

    private:
        /// The paths that this bubble holds
        map<string, set<uint32_t> > paths;
};

#endif // BUBBLE_H
