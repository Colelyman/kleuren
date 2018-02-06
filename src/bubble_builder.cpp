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

    // if there is no endKmer, return an empty bubble
    if(!graph->isValidBFTKmer(endBftKmer)) {
        if(endBftKmer != NULL) {
            free_BFT_kmer(endBftKmer, 1);
        }
        return bubble;
    }

    map<uint32_t*, string, uint32Cmp> paths = this->extendPaths(startBftKmer, endBftKmer, maxDepth);
    free_BFT_kmer(startBftKmer, 1);
    free_BFT_kmer(endBftKmer, 1);

	for(const auto& element : paths) {
		Path path = Path(element.second);
		bubble.addPath(path, element.first);
	}

    return bubble;
}

void freeQueue(list<BFT_kmer*> queue) {
    while(!queue.empty()) {
        printf("in freeQueue, popping off the first element\n");
        BFT_kmer* currentBftKmer = queue.front();
        free_BFT_kmer(currentBftKmer, 1);
        queue.pop_front();
    }
}

BFT_kmer* BubbleBuilder::findEndBftKmer(BFT_kmer* startBftKmer, uint32_t numColors, uint32_t maxDepth) {
    list<BFT_kmer*> queue;
    // set the graph to be able to mark kmers
    graph->setMarking();

    graph->markBFTKmer(startBftKmer);
    queue.push_back(startBftKmer);

    uint32_t depth = 0;
    // loop until a kmer is found or there are no more neighbors to check
    while(!queue.empty() && depth < maxDepth) {
        BFT_kmer* currentBftKmer = queue.front();
        queue.pop_front();

        printf("popped off kmer: %s\n", currentBftKmer->kmer);
        BFT_kmer* neighbors = graph->getSuffixNeighbors(currentBftKmer);
        for(size_t i = 0; i < 4; i++) {
            if(graph->isValidBFTKmer(neighbors + i)) {
                printf("\tkmer is valid\n");
                if(!graph->isMarkedBFTKmer(neighbors + i)) {
                    printf("\tkmer is not marked, adding to the queue\n");
                    graph->markBFTKmer(neighbors + i);
                    BFT_kmer* neighborCopy = malloc(sizeof(BFT_kmer));
                    memcpy(neighborCopy, neighbors + i, sizeof(BFT_kmer));
                    queue.push_back(neighbors + i);
                    if(graph->getNumColors(neighbors + i) >= numColors) {
                        printf("\tan end kmer has been found!\n");
                        free_BFT_kmer(currentBftKmer, 1);
                        freeQueue(queue);
                        graph->clearMarking();
                        return neighbors + i;
                    }
                    printf("\tcontinuing\n");
                    continue;
                }
            }
        }
        free_BFT_kmer(neighbors, 4);

        printf("\tfreeing the currentBftKmer: %s\n", currentBftKmer->kmer);
        free_BFT_kmer(currentBftKmer, 1);

        depth++;
    }
    printf("freeing the queue\n");
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

bool BubbleBuilder::recursiveExtend(BFT_kmer* currentBftKmer, uint32_t currentColor, uint32_t** intersectingColors, BFT_kmer* endBftKmer, string& path, list<BFT_kmer*>& toFree, uint32_t depth, uint32_t maxDepth) {
    // mark the currentBftKmer as visited
    graph->markBFTKmer(currentBftKmer);
    // the maxDepth has been reached, therefore return an empty path 
    if(depth >= maxDepth) {
        path = "";
        return false;
    }

    // the base case is reached when the currentKmer is the same as the endKmer
    if(!strcmp(currentBftKmer->kmer, endBftKmer->kmer)) {
        return true;
    }

    BFT_kmer* neighbors = graph->getSuffixNeighbors(currentBftKmer);
    toFree.push_back(neighbors);
    for(size_t i = 0; i < 4; i++) {
        BFT_kmer* neighbor = neighbors + i;
        if(!graph->isValidBFTKmer(neighbor) || graph->isMarkedBFTKmer(neighbor)) { // the kmer is invalid or has already been visited, thus skip it
            continue;
        }
        uint32_t* neighborColors = graph->getColors(neighbor);
        // check if the neighbor has the currentColor
        if(!isColorContained(currentColor, neighborColors)) {
            free(neighborColors);
            continue;
        }
 
        uint32_t* prevIntersectingColors = *intersectingColors;
        *intersectingColors = intersection_uint32(prevIntersectingColors, neighborColors);
        free(prevIntersectingColors);
        free(neighborColors);
        size_t neighborLen = strlen(neighbor->kmer);
        string oldPath = path;
        char neighborSuffix;
        strncpy(neighborSuffix, neighbors->kmer + neighborLen - 1, 1);
        path.append(1, neighborSuffix);
        depth++;
        if(!recursiveExtend(neighbor, currentColor, intersectingColors, endBftKmer, path, toFree, depth, maxDepth)) {
            path = oldPath;
        }
        else {
            return true;
        }
    }
}

map<uint32_t*, string, uint32Cmp> BubbleBuilder::extendPaths(BFT_kmer* startBftKmer, BFT_kmer* endBftKmer, uint32_t maxDepth) {
	map<uint32_t*, string, uint32Cmp> paths;

    // a list that holds the BFT_kmer neighbor arrays to free after extending the paths
    list<BFT_kmer*> toFree;

    list<uint32_t> colorQueue;

    // add each color to the colorQueue
    uint32_t* colors = graph->getColors(startBftKmer);
    for(uint32_t i = 1; i <= colors[0]; i++) {
        colorQueue.push_back(colors[i]);
    }

    graph->setMarking();

    while(!colorQueue.empty()) {
        uint32_t currentColor = colorQueue.front();
        colorQueue.pop_front();
        string path;
        recursiveExtend(startBftKmer, currentColor, &colors, endBftKmer, path, toFree, 0, maxDepth);
        paths[colors] = path;

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
    }

    graph->clearMarking();

    while(!toFree.empty()) {
        BFT_kmer* neighbors = toFree.front();
        free_BFT_kmer(neighbors, 4);
        toFree.pop_front();
    }

    return paths;
}
