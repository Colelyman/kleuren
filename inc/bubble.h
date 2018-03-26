/**
 * @class Bubble
 *
 * Bubble represents a set of paths for 2 or more colors that share a common
 * starting and ending node. 
 *
 * @author Cole Lyman
 *
 * @date 2017/6/21
 *
 */

#ifndef BUBBLE_H
#define BUBBLE_H

#include <vector>

#include "path.h"

using std::vector;

class Bubble {
    
    public:
        Bubble();

        /// Checks if the path is present in the bubble
        bool pathExists(Path pathCandidate) const;

        /// Checks if a bubble is valid, meaning it fits the following criteria:
        /// * there is more than one path
        /// * none of the paths are empty
        /// * at least n colors are present in the bubble
        /// * there are no paths that have overlapping colors
        bool isValid(size_t kmerLen, uint32_t n) const;

        /** 
         * Adds a path to paths, and appends the color to the corresponding path
         * if the path is already contained in colors.
         * @param path the path to add to paths
         */
        void addPath(Path path);

        /// Returns the paths of the bubble
        vector<Path> getPaths() const;

    private:
        /// The paths that this bubble holds
        vector<Path> paths;

};

#endif // BUBBLE_H
