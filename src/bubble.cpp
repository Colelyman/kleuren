/*
 * Implementation of bubble.h
 */

#include "bubble.h"

Bubble::Bubble() {

}

map<pair<int, int>, int> Bubble::runNW() {
    map<pair<int, int>, int> results;
    // iterate over each pair of paths in this->paths
    for(unsigned int i = 0; i < paths.size() - 1; i++) {
        for(unsigned int j = i + 1; j < paths.size(); j++) {
            pair<int, int> currentPair;
            currentPair.first = paths[i].getColorID();
            currentPair.second = paths[j].getColorID();

            int score = paths[i].runNW(paths[j]);

            results[currentPair] = score;
        }
    }
}
