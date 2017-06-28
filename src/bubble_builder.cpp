/*
 * Implementation of bubble_builder.h
 */

#include <vector>
#include <utility>
#include <set>

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
    Color* color = *colors.getColors().begin();

    // find the next kmer that occurs in all of the colors
    string endKmer = findEndKmer(startKmer, color, colors);
    
    /// @todo add a check if there is no endKmer in color...?

    vector<Path> paths;
    // extend the path from kmer to endKmer for each color in colors
    for(set<Color*>::iterator it = colors.getBeginIterator(); it != colors.getEndIterator(); ++it) {
        Path path = extendPath(startKmer, endKmer, *it);
        paths.push_back(path);
    }

    return bubble;
}

string BubbleBuilder::findEndKmer(string& startKmer, Color* color, ColorSet colors) {
    string currentKmer = startKmer;
    vector<string> neighbors;
    
    // should this function be recursive...?

    // loop until the currentKmer is in all of the colors
    while(!colors.allContainsKmer(currentKmer)) {
        neighbors = color->getSuffixNeighbors(currentKmer);
        for(string neighbor : neighbors) {
            // explore the path for each kmer... 
        }
    }

    return endKmerIdx;
}

Path BubbleBuilder::extendPath(size_t startIdx, size_t endIdx, Color* color) {
    size_t currentIdx = startIdx; 
    string currentKmer = color->extractSubstring(startIdx, kmerLen);
    Path path = Path(color);

    while(currentIdx != endIdx) {
        path.addIndex(currentIdx);
        vector<string> suffixNeighbors = color->getSuffixNeighbors(currentKmer);
        for(string neighbor : suffixNeighbors) {
            // extend the possible paths for each of the neighbors
        }

        break; // remove when the logic is actually implemented
    }

    return path;
}
