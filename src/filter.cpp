/**
 * Implementation of the Filter functions.
 */

#include "filter.h"

Filter::Filter(Graph* graph) {
    this->graph = graph;
}

bool Filter::filterStart(BFT_kmer* bftKmer, uint32_t n, BubbleStats* bubbleStats) {
    if(bftKmer != NULL) {
        if(graph->isValidBFTKmer(bftKmer)) {
            bubbleStats->incNumVisitedNodes();
            uint32_t numColors = graph->getNumColors(bftKmer);
            bubbleStats->incNumColorsInNodes(numColors);
            if(numColors >= n) {
                if(graph->hasSuffixNeighbors(bftKmer)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Filter::filterEnd(BFT_kmer* bftKmer, uint32_t n, BubbleStats* bubbleStats) {
    if(bftKmer != NULL) {
        if(graph->isValidBFTKmer(bftKmer)) {
            if(graph->getNumColors(bftKmer) >= n) {
                return true;
            }
        }
    }
    return false;
}

bool Filter::filterMiddle(BFT_kmer* bftKmer, BubbleStats* bubbleStats) {
    if(bftKmer != NULL) {
        if(graph->isValidBFTKmer(bftKmer)) {
            bubbleStats->incNumVisitedNodes();
            uint32_t numColors = graph->getNumColors(bftKmer);
            bubbleStats->incNumColorsInNodes(numColors);
            if(graph->hasSuffixNeighbors(bftKmer)) {
                return true;
            }
        }
    }
    return false;
}
