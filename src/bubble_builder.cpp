/*
 * Implementation of bubble_builder.h
 */

#include <vector>
#include <utility>
#include <set>
#include <cstring>
#include <assert.h>
#include <iostream>
#include <algorithm>

#include "bubble_builder.h"

using std::vector;
using std::pair;
using std::set;
using std::cerr;
using std::endl;
using std::random_shuffle;

BubbleBuilder::BubbleBuilder(Graph* graph) {
    this->graph = graph;
}

Bubble BubbleBuilder::build(BFT_kmer* startBftKmer, uint32_t numColors, uint32_t maxDepth) {
    Bubble bubble = Bubble();

	// if the color doesn't have any suffix neighbors, return an empty bubble
	if(!graph->hasSuffixNeighbors(startBftKmer)) {
		return bubble;
	}

	// find the next kmer that occurs in all of the colors
    BFT_kmer* endBftKmer = findEndBftKmer(startBftKmer, numColors);

    // if there is no endKmer, return an empty bubble
    if(!graph->isValidBFTKmer(endBftKmer)) {
        return bubble;
    }

	map<bit_vector, string> paths = this->extendPaths(startBftKmer, endBftKmer, maxDepth);
	for(const auto& element : paths) {
		Path path = Path(element.second);
		bubble.addPath(path, element.first);
	}

    return bubble;
}

/**
 * Helper function to get the neighbors of vertices
 * @param vertices the kmers to get the neighbors from
 * @return a vector of type Vertex with all of the neighbors of the vertices 
 */
vector<BFT_kmer*> BubbleBuilder::getNeighbors(vector<BFT_kmer*> bftKmers) {
    vector<BFT_kmer*> neighbors;
    for(BFT_kmer* bftKmer : bftKmers) {
        BFT_kmer* neighborArray = graph->getSuffixNeighbors(bftKmer);
        if(neighborArray == NULL) {
            continue;
        }
        for(BFT_kmer* neighbor : arrayToVector(neighborArray)) {
            if(graph->isValidBFTKmer(neighbor)) {
                neighbors.push_back(neighbor);
            }
        }
    }

    return neighbors;
}

vector<BFT_kmer*> BubbleBuilder::arrayToVector(BFT_kmer* neighborPtrs) {
    vector<BFT_kmer*> neighbors;
    for(size_t i = 0; i < 4; i++) {
        neighbors.push_back(neighborPtrs + i);
    }

    return neighbors;
}

BFT_kmer* BubbleBuilder::findEndBftKmer(BFT_kmer* startBftKmer, uint32_t numColors) {
    vector<BFT_kmer*> neighbors = arrayToVector(graph->getSuffixNeighbors(startBftKmer));

    // loop until a kmer is found or there are no more neighbors to check
    while(true) {
        neighbors = getNeighbors(neighbors);
        if(neighbors.size() == 0) { // there are no neighbors to check, so break out of the loop
            break;
        }

        for(BFT_kmer* neighbor : neighbors) {
            if(graph->getNumColors(neighbor) >= numColors) {
                return neighbor;
            }
        }
    }

    // there is no kmer in color that is present in all colors
    return NULL; 
}

bit_vector BubbleBuilder::getBitvector(BFT_kmer* bftKmer) {
    uint32_t* colorArray = graph->getColors(bftKmer);
    bit_vector colors(graph->getNumColors(), 0);
    for(size_t i = 1; i <= colorArray[0]; i++) {
        colors[colorArray[i] - 1] = 1;
    }

    return colors;
}

bool BubbleBuilder::recursiveExtend(BFT_kmer* currentBftKmer, BFT_kmer* endBftKmer, map<bit_vector, string>& paths, set<BFT_kmer*>& visited, uint32_t depth, uint32_t maxDepth) {
    // mark the currentBftKmer as visited
    // TODO perhaps convert to marking the BFT_kmers in the BFT
    visited.insert(currentBftKmer);
    // the maxDepth has been reached, therefore return an empty path 
    if(depth >= maxDepth) {
		// clear out paths?
        paths.clear();
        return false;
    }

    // the base case is reached when the currentKmer is the same as the endKmer
    if(currentBftKmer->kmer == endBftKmer->kmer) {
        return true;
    }

    vector<BFT_kmer*> neighbors = arrayToVector(graph->getSuffixNeighbors(currentBftKmer));
    // shuffle the neighbors vector so that there is no bias towards A
    random_shuffle(neighbors.begin(), neighbors.end());
    for(BFT_kmer* neighbor : neighbors) {
        if(visited.find(neighbor) != visited.end()) { // the kmer has already been visited, thus skip it
            continue;
        }
        size_t neighborLen = strlen(neighbor->kmer);
        char neighborSuffix;
        strncpy(neighborSuffix, neighbor->kmer + neighborLen - 1, 1);
        bit_vector colors = getBitvector(neighbor);
        string oldPath = paths[colors];
        paths[colors].append(1, neighborSuffix);
        depth += 1;
        if(!recursiveExtend(neighbor, endBftKmer, paths, visited, depth, maxDepth)) {
            paths[colors] = oldPath;
        }
        else {
            return true;
        }
    }
}

map<bit_vector, string> BubbleBuilder::extendPaths(BFT_kmer* startBftKmer, BFT_kmer* endBftKmer, uint32_t maxDepth) {
	map<bit_vector, string> paths;

    set<BFT_kmer*> visited;

    recursiveExtend(startBftKmer, endBftKmer, paths, visited, 0, maxDepth);

    return paths;
}
