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

Bubble BubbleBuilder::build(Vertex& startVertex, unsigned int numColors, unsigned int maxDepth) {
    Bubble bubble = Bubble();

	// if the color doesn't have any suffix neighbors, return an empty bubble
	if(!graph->hasSuffixNeighbors(startVertex)) {
		return bubble;
	}

	// find the next kmer that occurs in all of the colors
    Vertex endVertex = findEndVertex(startVertex, numColors);

    // if there is no endKmer, return an empty bubble
    if(endVertex.getKmer().empty()) {
        return bubble;
    }

	map<bit_vector, string> paths = this->extendPaths(startVertex, endVertex, maxDepth);
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
vector<Vertex> BubbleBuilder::getNeighbors(vector<Vertex> vertices) {
    vector<Vertex> neighbors;
    for(Vertex vertex : vertices) {
        for(Vertex neighbor : graph->getSuffixNeighbors(vertex)) {
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

Vertex BubbleBuilder::findEndVertex(Vertex& startVertex, unsigned int numColors) {
    vector<Vertex> neighbors = graph->getSuffixNeighbors(startVertex);

    // loop until a kmer is found or there are no more neighbors to check
    while(true) {
        neighbors = getNeighbors(neighbors);
        if(neighbors.size() == 0) { // there are no neighbors to check, so break out of the loop
            break;
        }

        for(Vertex neighbor : neighbors) {
            if(neighbor.getNumColors() >= numColors) {
                return neighbor;
            }
        }
    }

    // there is no kmer in color that is present in all colors
    return Vertex("", 0);
}

bool BubbleBuilder::recursiveExtend(Vertex& currentVertex, Vertex& endVertex, map<bit_vector, string>& paths, set<Vertex>& visited, unsigned int depth, unsigned int maxDepth) {
    // mark the currentVertex as visited
    visited.insert(currentVertex);
    // the maxDepth has been reached, therefore return an empty path 
    if(depth >= maxDepth) {
		// clear out paths?
        paths.clear();
        return false;
    }

    // the base case is reached when the currentKmer is the same as the endKmer
    if(currentVertex == endVertex) {
        return true;
    }

    vector<Vertex> neighbors = graph->getSuffixNeighbors(currentVertex);
    // shuffle the neighbors vector so that there is no bias towards A
    random_shuffle(neighbors.begin(), neighbors.end());
    for(Vertex neighbor : neighbors) {
        if(visited.find(neighbor) != visited.end()) { // the kmer has already been visited, thus skip it
            continue;
        }
        string neighborSuffix = neighbor.getKmer().substr(neighbor.getKmer().length() - 1, 1);
        string oldPath = paths[neighbor.getColors()];
        paths[neighbor.getColors()] += neighborSuffix;
        depth += 1;
        if(!recursiveExtend(neighbor, endVertex, paths, visited, depth, maxDepth)) {
            paths[neighbor.getColors()] = oldPath;
        }
        else {
            return true;
        }
    }
}

map<bit_vector, string> BubbleBuilder::extendPaths(Vertex& startVertex, Vertex& endVertex, unsigned int maxDepth) {
	map<bit_vector, string> paths;

    set<Vertex> visited;

    recursiveExtend(startVertex, endVertex, paths, visited, 0, maxDepth);

    return paths;
}
