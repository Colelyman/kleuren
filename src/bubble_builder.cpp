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
    set<Color*>::iterator colorIt = colors.getBeginIterator();

    // find the next kmer that occurs in all of the colors
    // loop until there is an endKmer, or all colors have been tried
    /// @todo this loop could be optimized...
    string endKmer = "";
    while(strcmp(endKmer.c_str(), "") == 0 && colorIt != colors.getEndIterator()) {
        endKmer = findEndKmer(startKmer, *colorIt++, colors);
    }

    // assert that an endKmer exists for this bubble
    assert(strcmp(endKmer.c_str(), "") != 0);

    vector<string> paths;
    // extend the path from kmer to endKmer for each color in colors
    for(set<Color*>::iterator it = colors.getBeginIterator(); it != colors.getEndIterator(); ++it) {
        string path = this->extendPath(startKmer, endKmer, *it, maxDepth);
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

set<string> getNeighbors(set<string> kmers, const Color* color) {
    set<string> neighbors;
    for(string kmer : kmers) {
        for(string neighbor : color->getSuffixNeighbors(kmer)) {
            neighbors.insert(neighbor);
        }
    }

    return neighbors;
}

void recursiveExtend(const string& currentKmer, const string& endKmer, string& path, const Color* color, set<string>& visited, unsigned int depth, unsigned int maxDepth) {
    // mark the currentKmer as visited
    visited.insert(currentKmer);
    cerr << "In recursiveExtend" << endl;
    cerr << "currentKmer: " << currentKmer << " endKmer: " << endKmer << endl;
    // the maxDepth has been reached, therefore return an empty path 
    if(depth >= maxDepth) {
        path = "";
        return;
    }

    // the base case is reached when the currentKmer is the same as the endKmer
    if(strcmp(currentKmer.c_str(), endKmer.c_str()) == 0) {
        cerr << "Returning: " << path << endl;
        return;
    }

    // call recursiveExtend on each of the neighbors of currentKmer
    vector<string> neighbors = getNeighbors(color->getSuffixNeighbors(currentKmer), color);
    random_shuffle(neighbors.begin(), neighbors.end());
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
        string neighborSuffix = neighbor.substr(1, neighbor.length() - 1);
        path += neighborSuffix;
        depth += 1;
        cerr << "\tdepth: " << depth << endl;
        cerr << "\tpath: " << path << endl;
        recursiveExtend(neighbor, endKmer, path, color, visited, depth, maxDepth);
    }
    cerr << "End of recursiveExtend with path: " << path << endl;
}

string BubbleBuilder::extendPath(string startKmer, string endKmer, const Color* color, unsigned int maxDepth) {
    cerr << "In extendPath" << endl;

    string path = startKmer;

    set<string> visited;

    recursiveExtend(startKmer, endKmer, path, color, visited, 0, maxDepth);

    return path;
}
