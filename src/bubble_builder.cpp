/*
 * Implementation of bubble_builder.h
 */

#include <vector>
#include <utility>
#include <set>
#include <cstring>
#include <assert.h>
#include <iostream>

#include "bubble_builder.h"

using std::vector;
using std::pair;
using std::set;
using std::cerr;
using std::endl;
using std::random_shuffle;

Bubble BubbleBuilder::build(string& startKmer, ColorSet colors, unsigned int maxDepth) {
    Bubble bubble = Bubble();
    // get the first color in ColorSet
    set<shared_ptr<Color> >::iterator colorIt = colors.getBeginIterator();

    // find the next kmer that occurs in all of the colors
    // loop until there is an endKmer, or all colors have been tried
    /// @todo this loop could be optimized...
    string endKmer = "";
    while(endKmer.empty() && colorIt != colors.getEndIterator()) {
        endKmer = findEndKmer(startKmer, *colorIt++, colors);
        cerr << "endKmer: " << endKmer << endl;
    }

    // if there is no endKmer, return an empty bubble
    if(endKmer.empty()) {
        //cerr << "no endKmer" << endl;
        return bubble;
    }

    // extend the path from kmer to endKmer for each color in colors
    for(set<shared_ptr<Color> >::iterator it = colors.getBeginIterator(); it != colors.getEndIterator(); ++it) {
        Path path = Path(this->extendPath(startKmer, endKmer, *it, maxDepth));
        bubble.addPath(path, *it);
    }

    return bubble;
}

/**
 * Helper function to get the neighbors in color of kmers.
 * @param kmers the kmers to get the neighbors from
 * @return a vector of type string with all of the neighbors of the kmers
 */
vector<string> getNeighbors(vector<string> kmers, const shared_ptr<Color> color) {
    vector<string> neighbors;
    for(string kmer : kmers) {
        for(string neighbor : color->getSuffixNeighbors(kmer)) {
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

string BubbleBuilder::findEndKmer(string& startKmer, const shared_ptr<Color> color, const ColorSet colors) {
    string revComp = reverseComplement(startKmer);
    vector<string> neighbors = color->getSuffixNeighbors(startKmer);

    // loop until a kmer is found or there are no more neighbors to check
    while(true) {
        neighbors = getNeighbors(neighbors, color);
        if(neighbors.size() == 0) { // there are no neighbors to check, so break out of the loop
            break;
        }

        for(string neighbor : neighbors) {
            if(colors.nContainsKmer(neighbor) && strcmp(neighbor.c_str(), revComp.c_str())) {
                return neighbor;
            }
        }
    }

    // there is no kmer in color that is present in all colors
    return "";
}

bool recursiveExtend(const string& currentKmer, const string& endKmer, string& path, const shared_ptr<Color> color, set<string>& visited, unsigned int depth, unsigned int maxDepth) {
    // mark the currentKmer as visited
    visited.insert(currentKmer);
    cerr << "In recursiveExtend" << endl;
    cerr << "currentKmer: " << currentKmer << " endKmer: " << endKmer << endl;
    // the maxDepth has been reached, therefore return an empty path 
    if(depth >= maxDepth) {
        cerr << "Returning false with path: " << path << endl;
        path = "";
        return false;
    }

    // the base case is reached when the currentKmer is the same as the endKmer
    if(strcmp(currentKmer.c_str(), endKmer.c_str()) == 0) {
        cerr << "Returning true with path: " << path << endl;
        return true;
    }

    vector<string> neighbors = color->getSuffixNeighbors(currentKmer);
    cerr << "\tneighbors: " << endl;
    for(string neighbor : neighbors) {
        if(visited.find(neighbor) == visited.end()) {
            cerr << "\t\t" << neighbor << endl;
        }
    }
    // randomly shuffle the neighbors of currentKmer
    for(string neighbor : neighbors) {
        if(visited.find(neighbor) != visited.end()) { // the kmer has already been visited, thus skip it
            cerr << "\t" << neighbor << " is visited!" << endl;
            continue;
        }
        cerr << "\tneighbor: " << neighbor << endl;
        string neighborSuffix = neighbor.substr(neighbor.length() - 1, 1);
        string oldPath = path;
        path += neighborSuffix;
        depth += 1;
        cerr << "\tdepth: " << depth << endl;
        cerr << "\tpath: " << path << endl;
        cerr << "\toldPath: " << oldPath << endl;
        if(!recursiveExtend(neighbor, endKmer, path, color, visited, depth, maxDepth)) {
            path = oldPath;
            cerr << "\tpath is now oldPath: " << path << endl;
        }
        else {
            cerr << "\tReturn true!" << endl;
            return true;
        }
    }
    cerr << "End of recursiveExtend with path: " << path << endl;
}

string BubbleBuilder::extendPath(string startKmer, string endKmer, const shared_ptr<Color> color, unsigned int maxDepth) {
    cerr << "In extendPath" << endl;

    string path = startKmer;

    set<string> visited;

    recursiveExtend(startKmer, endKmer, path, color, visited, 0, maxDepth);

    return path;
}
