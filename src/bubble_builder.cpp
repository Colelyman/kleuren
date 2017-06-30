/*
 * Implementation of bubble_builder.h
 */

#include <vector>
#include <utility>
#include <set>
#include <cstring>

#include "bubble_builder.h"

using std::vector;
using std::pair;
using std::set;

BubbleBuilder::BubbleBuilder(size_t len) {
    kmerLen = len;
}

Bubble BubbleBuilder::build(string& startKmer, ColorSet colors) {
    Bubble bubble = Bubble();
    // get the first color in ColorSet
    set<Color*>::iterator colorIt = colors.getBeginIterator();

    // find the next kmer that occurs in all of the colors
    // loop until there is an endKmer, or all colors have been tried
    /// @todo this loop could be optimized...
    string endKmer = "";
    while(strcmp(endKmer.c_str(), "") == 0 && colorIt != colors.getEndIterator()) {
        endKmer = findEndKmer(startKmer, *colorIt++, colors);
    }

    vector<Path> paths;
    // extend the path from kmer to endKmer for each color in colors
    for(set<Color*>::iterator it = colors.getBeginIterator(); it != colors.getEndIterator(); ++it) {
        Path path = this->extendPath(startKmer, endKmer, *it);
        paths.push_back(path);
    }

    return bubble;
}

/**
 * Helper function to get the neighbors in color of kmers.
 * @param kmers the kmers to get the neighbors from
 * @return a vector of type string with all of the neighbors of the kmers
 */
vector<string> getNeighbors(vector<string> kmers, const Color* color) {
    vector<string> neighbors;
    for(string kmer : kmers) {
        for(string neighbor : color->getSuffixNeighbors(kmer)) {
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

string BubbleBuilder::findEndKmer(string& startKmer, const Color* color, const ColorSet colors) {
    vector<string> neighbors({startKmer});

    while(true) {
        neighbors = getNeighbors(neighbors, color);
        if(neighbors.size() == 0) { // there are no neighbors to check, so break out of the loop
            break;
        }

        for(string neighbor : neighbors) {
            if(colors.allContainsKmer(neighbor)) {
                return neighbor;
            }
        }
    }

    // there is no kmer in color that is present in all colors
    return "";
}

Path BubbleBuilder::extendPath(string& startKmer, string& endKmer, const Color* color) {
    string currentKmer = startKmer;
    Path path = Path(color, kmerLen);

    while(currentKmer != endKmer) {
        //path.addIndex(currentIdx);
        vector<string> suffixNeighbors = color->getSuffixNeighbors(currentKmer);
        for(string neighbor : suffixNeighbors) {
            // extend the possible paths for each of the neighbors
        }

        break; // remove when the logic is actually implemented
    }

    return path;
}
