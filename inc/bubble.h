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
#include <vector>

#include "path.h"

using std::map;
using std::pair;
using std::vector;

class Bubble {
    
    public:
        /** 
         * Runs Needleman-Wunsch algorithm on each pair in a pair-wise fashion.
         * @return a map of key pair<int, int> where each int in the pair is the
         * ID of the colors compared, and value int which is the score for that 
         * pair of paths.
         */
        map<pair<int, int>, int> runNW();

    private:
        /// The paths that this bubble holds
        vector<Path> paths;

};

#endif // BUBBLE_H
