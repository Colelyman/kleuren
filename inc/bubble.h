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

#include <map>
#include <utility>
#include <set>

#include "path.h"

using std::map;
using std::pair;
using std::set;

class Bubble {
    
    public:
        Bubble();

        /** 
         * Runs Needleman-Wunsch algorithm on each pair in a pair-wise fashion.
         * @return a map of key pair<int, int> where each int in the pair is the
         * ID of the colors compared, and value int which is the score for that 
         * pair of paths.
         */
        map<pair<int, int>, int> runNW();

        /// Checks if the path is present in the bubble
        bool pathExists(Path path) const;

        /** 
         * Adds a path to paths, and appends the color to the corresponding path
         * if the path is already contained in colors.
         * @param path the path to add to paths
         * @param color the color that is associated with the path
         */
        void addPath(Path path, Color* color);

        /// Returns the colors that are associated with path
        set<Color*> getColors(Path path) const;

        /// Returns the name of the Colors that path is associated with
        vector<string> getColorNames(Path path) const;

        /// Returns the ID of the Colors that path is associated with
        vector<int> getColorIDs(Path path) const;

        /// Returns the paths of the bubble
        map<Path, set<Color*> > getPaths() const;

    private:
        /// The paths that this bubble holds
        map<Path, set<Color*> > paths;

};

#endif // BUBBLE_H
