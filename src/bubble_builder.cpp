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
#include "filter.h"

using std::vector;
using std::pair;
using std::set;
using std::cerr;
using std::endl;
using std::random_shuffle;

BubbleBuilder::BubbleBuilder(Graph* graph, BubbleStats* bubbleStats) :
    filter(graph) {
    this->graph = graph;
    this->bubbleStats = bubbleStats;
}

Bubble BubbleBuilder::build(BFT_kmer* startBFTKmer, uint32_t numColors, uint32_t maxDepth) {
    Bubble bubble = Bubble();
    bubbleStats->incNumVisitedNodes();

    if(!filter.filterStart(startBFTKmer, numColors, bubbleStats)) {
        free_BFT_kmer(startBFTKmer, 1);
        return bubble;
    }

    // find the next kmer that occurs in all of the colors
    BFT_kmer* endBFTKmer = findEndBFTKmer(startBFTKmer, numColors, maxDepth);

    // if there is no endKmer, or the endKmer is the same as the startKmer, return an empty bubble
    if(!graph->isValidBFTKmer(endBFTKmer) || strncmp(startBFTKmer->kmer, endBFTKmer->kmer, strlen(startBFTKmer->kmer)) == 0) {
        if(endBFTKmer != NULL) {
            free_BFT_kmer(endBFTKmer, 1);
        }
        free_BFT_kmer(startBFTKmer, 1);
        bubbleStats->incNumNoEndKmersFound();
        return bubble;
    }

    bubble = this->extendPaths(startBFTKmer, endBFTKmer, maxDepth);
    free_BFT_kmer(startBFTKmer, 1);
    free_BFT_kmer(endBFTKmer, 1);

    return bubble;
}

void freeQueue(list<BFT_kmer*> queue) {
    while(!queue.empty()) {
        BFT_kmer* currentBFTKmer = queue.front();
        free_BFT_kmer(currentBFTKmer, 1);
        queue.pop_front();
    }
}

BFT_kmer* BubbleBuilder::findEndBFTKmer(BFT_kmer* startBFTKmer, uint32_t numColors, uint32_t maxDepth) {
    list<BFT_kmer*> queue;
    list<uint32_t> depthQueue;

    BFT_kmer* startCopy = graph->getBFTKmer(startBFTKmer->kmer);
    uint32_t depth = 0;
    queue.push_back(startCopy), depthQueue.push_back(depth);

    // loop until a kmer is found or there are no more neighbors to check
    while(!queue.empty() && depth < maxDepth) {
        BFT_kmer* currentBFTKmer = queue.front();
        depth = depthQueue.front();
        queue.pop_front(), depthQueue.pop_front();

        // iterate over each of the neighbors for currentBFTKmer
        BFT_kmer* neighbors = graph->getSuffixNeighbors(currentBFTKmer);
        for(size_t i = 0; i < 4; i++) {
            if(filter.filterEnd(&neighbors[i], numColors, bubbleStats)) {
                free_BFT_kmer(currentBFTKmer, 1);
                free_BFT_kmer(neighbors, 4);
                freeQueue(queue);
                return graph->getBFTKmer(neighbors[i].kmer);
            }
            else {
                queue.push_back(graph->getBFTKmer(neighbors[i].kmer)), depthQueue.push_back(depth + 1);
            }
        }
        free_BFT_kmer(neighbors, 4);
        free_BFT_kmer(currentBFTKmer, 1);
    }
    freeQueue(queue);
    // there was no end node found given the specifications
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

uint32_t min(uint32_t a, uint32_t b) {
    if(a < b) {
        return a;
    }
    else {
        return b;
    }
}

// Adapted from @GuillaumeHolley's function
uint32_t* intersectColorArrays(uint32_t* a, uint32_t* b) {
    uint32_t i = 1, j = 1, it = 0;
    uint32_t aSize= a[0] + 1, sizeB = b[0] + 1;

    uint32_t* c = (uint32_t*) malloc(min(*a, *b) * sizeof(uint32_t));

    while(i < aSize && j < sizeB) {
        if(a[i] > b[j]) {
            j++;
        }
        else if(b[j] > a[i]){
            i++;
        }
        else {
            it++;
            c[it] = a[i];
            i++;
            j++;
        }
    }

    c[0] = it;

    return c;
}

bool BubbleBuilder::recursiveExtend(BFT_kmer* currentBFTKmer, uint32_t currentColor, uint32_t*& intersectingColors, BFT_kmer* endBFTKmer, string& path, uint32_t depth, uint32_t maxDepth) {
    // the maxDepth has been reached, therefore return an empty path
    if(depth >= maxDepth) {
        path = "";
        return false;
    }

    // the base case is reached when the currentKmer is the same as the endKmer
    if(!strncmp(currentBFTKmer->kmer, endBFTKmer->kmer, strlen(currentBFTKmer->kmer))) {
        return true;
    }

    // iterate over each of the neighbors to extend the path
    BFT_kmer* neighbors = graph->getSuffixNeighbors(currentBFTKmer);
    for(size_t i = 0; i < 4; i++) {
        if(!filter.filterMiddle(&neighbors[i], bubbleStats)) {
            continue;
        }
        BFT_kmer* neighbor = graph->getBFTKmer(neighbors[i].kmer);

        uint32_t* neighborColors = graph->getColors(neighbor);
        // check if the neighbor has the currentColor
        if(!isColorContained(currentColor, neighborColors)) {
            free_BFT_kmer(neighbor, 1);
            free(neighborColors);
            continue;
        }

        // find the intersection between the current intersectionColors and the neighborColors
        uint32_t* prevIntersectingColors = intersectingColors;
        intersectingColors = intersectColorArrays(prevIntersectingColors, neighborColors);
        free(prevIntersectingColors);
        free(neighborColors);

        // append the suffix of the neighbor to the path
        size_t neighborLen = strlen(neighbor->kmer);
        string oldPath = path;
        path.append(1, *(neighbor->kmer + neighborLen - 1));
        depth++;

        // recursively extend the path of the neighbor
        if(!recursiveExtend(neighbor, currentColor, intersectingColors, endBFTKmer, path, depth, maxDepth)) {
            // the path was a dead end, try the next neighbor
            path = oldPath;
            free_BFT_kmer(neighbor, 1);
        }
        else {
            // the path was complete, return up the tree with the true path
            free_BFT_kmer(neighbor, 1);
            free_BFT_kmer(neighbors, 4);
            return true;
        }
    }
    // a path hasn't been found, thus set path to ""
    path = ""; // TODO is this the right thing to do in this case?
    free_BFT_kmer(neighbors, 4);
    return false;
}

Bubble BubbleBuilder::extendPaths(BFT_kmer* startBFTKmer, BFT_kmer* endBFTKmer, uint32_t maxDepth) {
    Bubble bubble;

    list<uint32_t> colorQueue;

    // add each color to the colorQueue
    uint32_t* colors = graph->getColors(startBFTKmer);
    for(uint32_t i = 1; i <= colors[0]; i++) {
        colorQueue.push_back(colors[i]);
    }

    while(!colorQueue.empty()) {
        // get the currentColor for which the path will be extended
        uint32_t currentColor = colorQueue.front();
        colorQueue.pop_front();

        // initialize the path to begin with the startBFTKmer sequence
        string pathString(startBFTKmer->kmer);
        // check if paths can be extended for this color, if not return an empty bubble
        if(!recursiveExtend(startBFTKmer, currentColor, colors, endBFTKmer, pathString, 0, maxDepth)) {
            free(colors);
            return Bubble();
        }

        bubble.addPath(pathString, colors);

        // remove the colors from colorQueue that have been extended
        list<uint32_t>::iterator it = colorQueue.begin();
        while(it != colorQueue.end()) {
            for(uint32_t i = 1; i <= colors[0]; i++) {
                if(*it == colors[i]) {
                    it = colorQueue.erase(it);
                    break;
                }
            }
            ++it;
        }
        free(colors);

        // get the colors of the startBFTKmer to extend the next path
        colors = graph->getColors(startBFTKmer);
    }

    free(colors);

    return bubble;
}
