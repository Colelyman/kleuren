/*
 * Implementation of graph.h.
 */

#include "graph.h"

#define V_VISITED 1 // for marking the BFT_kmer as visited

Graph::Graph(char* bftFileName) {
    bft = load_BFT(bftFileName);
    free(bftFileName);
    //set_neighbors_traversal(bft);
}

Graph::~Graph() {
    free_cdbg(bft);
}

bool Graph::isBFTKmer(char* strKmer) const {
    uint32_t* colorSet = query_sequence(bft, strKmer, 0.001, false);
    if(colorSet == NULL) {
        return false;
    }
    uint32_t numColors = colorSet[0];
    free(colorSet);
    if(numColors) {
        return true;
    }
    return false;
}

BFT_kmer* Graph::getBFTKmer(char* strKmer) const {
    if(isBFTKmer(strKmer)) {
        return get_kmer(strKmer, bft);
    }
    return NULL;
}

bool Graph::isValidBFTKmer(BFT_kmer* bftKmer) const {
    if(bftKmer != NULL) {
        if(is_kmer_in_cdbg(bftKmer)) {
            return true;
        }
    }
    return false;
}

void Graph::setMarking() {
    //set_marking(bft);
    visited.clear();
}

void Graph::clearMarking() {
    //unset_marking(bft);
    visited.clear();
}

void Graph::markBFTKmer(BFT_kmer* bftKmer) {
    //set_flag_kmer(V_VISITED, bftKmer, bft);
    //visited.insert(bftKmer->kmer);
    //printf("\tvisited size is: %lu\n", visited.size());
}

bool Graph::isMarkedBFTKmer(BFT_kmer* bftKmer) const {
    /*
    if(get_flag_kmer(bftKmer, bft) == V_VISITED) {
        return true;
    }
    return false;
    */
    if(visited.find(bftKmer->kmer) != visited.end()) {
        return true;
    }
    return false;
}

uint32_t Graph::getNumColors(BFT_kmer* bftKmer) const {
    uint32_t numColors = 0;
    BFT_annotation* bftAnno = get_annotation(bftKmer);
    uint32_t* temp = get_list_id_genomes(bftAnno, bft);
    numColors = temp[0];
    free_BFT_annotation(bftAnno);
    free(temp);

    return numColors;
}

uint32_t Graph::getNumColors() const {
    return bft->nb_genomes;
}

uint32_t* Graph::getColors(BFT_kmer* bftKmer) const {
    BFT_annotation* bftAnno = get_annotation(bftKmer);

    uint32_t* colors = get_list_id_genomes(bftAnno, bft);
    free_BFT_annotation(bftAnno);
    return colors;
}

char* Graph::getColorFilePath(uint32_t colorId) const {
    return bft->filenames[colorId];
}

BFT_kmer* Graph::getSuffixNeighbors(BFT_kmer* bftKmer) const {
    if(is_kmer_in_cdbg(bftKmer)) {
        return get_successors(bftKmer, bft);
    }
    return NULL;
}

bool Graph::hasSuffixNeighbors(BFT_kmer* bftKmer) const {
    BFT_kmer* neighbors = getSuffixNeighbors(bftKmer);
    if(neighbors == NULL) {
        return false;
    }
    bool hasNeighbors = !(checkIfEmpty(neighbors));
    free_BFT_kmer(neighbors, 4);
    return hasNeighbors;
}

BFT_kmer* Graph::getPrefixNeighbors(BFT_kmer* bftKmer) const {
    if(is_kmer_in_cdbg(bftKmer)) {
        return get_predecessors(bftKmer, bft);
    }
    return NULL;
}

bool Graph::hasPrefixNeighbors(BFT_kmer* bftKmer) const {
    BFT_kmer* neighbors = getPrefixNeighbors(bftKmer);
    if(neighbors == NULL) {
        return false;
    }
    bool hasNeighbors = !(checkIfEmpty(neighbors));
    free_BFT_kmer(neighbors, 4);
    return hasNeighbors;
}

bool Graph::checkIfEmpty(BFT_kmer* bftKmers) const {
    for(uint32_t i = 0; i < 4; i++) {
        if(isValidBFTKmer(bftKmers + i)) {
            return false;
        }
    }
    return true;
}
