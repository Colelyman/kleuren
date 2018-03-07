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
        free_BFT_kmer(startBftKmer, 1);
		return bubble;
	}

	// find the next kmer that occurs in all of the colors
    BFT_kmer* endBftKmer = findEndBftKmer(startBftKmer, numColors, maxDepth);

    // if there is no endKmer, or the endKmer is the same as the startKmer, return an empty bubble
    if(!graph->isValidBFTKmer(endBftKmer) || strncmp(startBftKmer->kmer, endBftKmer->kmer, strlen(startBftKmer->kmer)) == 0) {
        if(endBftKmer != NULL) {
            free_BFT_kmer(endBftKmer, 1);
        }
        free_BFT_kmer(startBftKmer, 1);
        return bubble;
    }

    bubble = this->extendPaths(startBftKmer, endBftKmer, maxDepth);
    free_BFT_kmer(startBftKmer, 1);
    free_BFT_kmer(endBftKmer, 1);

    return bubble;
}

void freeQueue(list<BFT_kmer*> queue) {
    while(!queue.empty()) {
        BFT_kmer* currentBftKmer = queue.front();
        free_BFT_kmer(currentBftKmer, 1);
        queue.pop_front();
    }
}

BFT_kmer* BubbleBuilder::findEndBftKmer(BFT_kmer* startBftKmer, uint32_t numColors, uint32_t maxDepth) {
    list<BFT_kmer*> queue;
    list<uint32_t> depthQueue;
    // set the graph to be able to mark kmers
    graph->setMarking();

    graph->markBFTKmer(startBftKmer);
    BFT_kmer* startCopy = graph->getBFTKmer(startBftKmer->kmer);
    queue.push_back(startCopy), depthQueue.push_back(0);

    // loop until a kmer is found or there are no more neighbors to check
    while(!queue.empty() && depth < maxDepth) {
        BFT_kmer* currentBftKmer = queue.front();
        uint32_t depth = depthQueue.front();
        queue.pop_front(), depthQueue.pop_front();

        // iterate over each of the neighbors for currentBftKmer
        BFT_kmer* neighbors = graph->getSuffixNeighbors(currentBftKmer);
        for(size_t i = 0; i < 4; i++) {
            if(graph->isValidBFTKmer(&neighbors[i])) {
                BFT_kmer* neighborCopy = graph->getBFTKmer(neighbors[i].kmer);
                if(neighborCopy == NULL) {
                    continue;
                }
                // check if neighborCopy has been visited
                if(!graph->isMarkedBFTKmer(neighborCopy)) {
                    graph->markBFTKmer(neighborCopy);
                    queue.push_back(neighborCopy), depthQueue.push_back(depth + 1);
                    // check if neigborCopy has enough colors to be an end BftKmer
                    if(graph->getNumColors(neighborCopy) >= numColors) {
                        graph->clearMarking();
                        free_BFT_kmer(currentBftKmer, 1);
                        free_BFT_kmer(neighbors, 4);
                        queue.pop_back(); // so that neighborCopy doesn't get free'd
                        freeQueue(queue);
                        return neighborCopy;
                    }
                }
            }
        }
        free_BFT_kmer(neighbors, 4);

        free_BFT_kmer(currentBftKmer, 1);
    }
    freeQueue(queue);
    // clear all of the markings in the graph
    graph->clearMarking();
    // there is no kmer in color that is present in all colors
    return NULL; 
}

bool isColorContained(uint32_t color, uint32_t* colorSet) {
    for(uint32_t i = 1; i <= colorSet[0]; i++) {
        if(color == colorSet[i]) {
            return true;
        }
    }
    return false;
}

bool BubbleBuilder::recursiveExtend(BFT_kmer* currentBftKmer, uint32_t currentColor, uint32_t** intersectingColors, BFT_kmer* endBftKmer, string& path, uint32_t depth, uint32_t maxDepth) {
    // mark the currentBftKmer as visited
    graph->markBFTKmer(currentBftKmer);
    // the maxDepth has been reached, therefore return an empty path 
    if(depth >= maxDepth) {
        path = "";
        return false;
    }

    // the base case is reached when the currentKmer is the same as the endKmer
    if(!strncmp(currentBftKmer->kmer, endBftKmer->kmer, strlen(currentBftKmer->kmer))) {
        return true;
    }

    // iterate over each of the neighbors to extend the path
    BFT_kmer* neighbors = graph->getSuffixNeighbors(currentBftKmer);
    for(size_t i = 0; i < 4; i++) {
        BFT_kmer* neighbor = graph->getBFTKmer(neighbors[i].kmer);
        if(neighbor == NULL) {
            continue;
        }
        
        if(!graph->isValidBFTKmer(neighbor) || graph->isMarkedBFTKmer(neighbor)) { // the kmer is invalid or has already been visited, thus skip it
            free_BFT_kmer(neighbor, 1);
            continue;
        }
        uint32_t* neighborColors = graph->getColors(neighbor);
        // check if the neighbor has the currentColor
        if(!isColorContained(currentColor, neighborColors)) {
            free_BFT_kmer(neighbor, 1);
            free(neighborColors);
            continue;
        }
 
        // find the intersection between the current intersectionColors and the neighborColors
        uint32_t* prevIntersectingColors = *intersectingColors;
        *intersectingColors = intersection_uint32(prevIntersectingColors, neighborColors);
        free(prevIntersectingColors);
        free(neighborColors);

        // append the suffix of the neighbor to the path
        size_t neighborLen = strlen(neighbor->kmer);
        string oldPath = path;
        path.append(1, *(neighbor->kmer + neighborLen - 1));
        depth++;

        // recursively extend the path of the neighbor
        if(!recursiveExtend(neighbor, currentColor, intersectingColors, endBftKmer, path, depth, maxDepth)) {
            // the path was a dead end, try the next neighbor
            path = oldPath;
            free_BFT_kmer(neighbor, 1);
        }
        else {
            // the path was complete, return up the tree with true
            free_BFT_kmer(neighbor, 1);
            free_BFT_kmer(neighbors, 4);
            return true;
        }
    }
    // a path hasn't been found, thus set path to ""
    path = "";
    free_BFT_kmer(neighbors, 4);
    return false;
}

Bubble BubbleBuilder::extendPaths(BFT_kmer* startBftKmer, BFT_kmer* endBftKmer, uint32_t maxDepth) {
    Bubble bubble;

    list<uint32_t> colorQueue;

    // add each color to the colorQueue
    uint32_t* colors = graph->getColors(startBftKmer);
    for(uint32_t i = 1; i <= colors[0]; i++) {
        colorQueue.push_back(colors[i]);
    }

    graph->setMarking();

    while(!colorQueue.empty()) {
        // get the currentColor for which the path will be extended
        uint32_t currentColor = colorQueue.front();
        colorQueue.pop_front();

        // initialize the path to begin with the startBftKmer sequence
        string pathString(startBftKmer->kmer);
        // check if paths can be extended for this color, if not return an empty bubble
        if(!recursiveExtend(startBftKmer, currentColor, &colors, endBftKmer, pathString, 0, maxDepth)) {
            free(colors);
            return Bubble();
        }

        // a path has been found represented by pathString
        Path path = Path(pathString);
        
        // for each of the colors represented by pathString, add the colorName to the path
        for(uint32_t i = 1; i <= colors[0]; i++) {
            string colorName(graph->getColorFilePath(colors[i]));
            path.addColorName(colorName);
        }

        // add the path to the bubble
        bubble.addPath(path);

        // remove the colors from colorQueue that have been extended
        list<uint32_t>::iterator it = colorQueue.begin();
        while(it != colorQueue.end()) {
            for(uint32_t i = 1; i <= colors[0]; i++) {
                if(*it == colors[i]) {
                    it = colorQueue.erase(it);
                }
            }
            ++it;
        }
        free(colors);

        // get the colors of the startBftKmer to extend the next path
        colors = graph->getColors(startBftKmer);
    }

    free(colors);

    graph->clearMarking();

    return bubble;
}
