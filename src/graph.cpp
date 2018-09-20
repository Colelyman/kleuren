/*
 * Implementation of graph.h.
 */

#include "graph.h"

Graph::Graph(char* bftFileName) {
    bft = load_BFT(bftFileName);
    free(bftFileName);
    //set_neighbors_traversal(bft);
}

Graph::~Graph() {
    free_cdbg(bft);
}

bool Graph::isBFTKmer(char* kmer) const {
    uint32_t* colorSet = query_sequence(bft, kmer, 0.001, false);
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

BFT_kmer* Graph::getBFTKmer(char* kmer) const {
    if(isBFTKmer(kmer)) {
        return get_kmer(kmer, bft);
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

vector<BFT_kmer*> Graph::getSuffixNeighbors(char* kmer) const {
    vector<BFT_kmer*> neighbors;
    uint32_t len = strlen(kmer);
    char* neighborKmer = (char*) malloc(len + 1);
    memcpy(neighborKmer, kmer + 1, (len - 1) * sizeof(char));
    for(int i = 0; i < 4; i++) {
        switch(i) {
            case 0: neighborKmer[len - 1] = 'A'; break;
            case 1: neighborKmer[len - 1] = 'C'; break;
            case 2: neighborKmer[len - 1] = 'G'; break;
            case 3: neighborKmer[len - 1] = 'T'; break;
        }
        BFT_kmer* neighbor = getBFTKmer(neighborKmer);
        if(neighbor != NULL) {
            if(isValidBFTKmer(neighbor)) {
                neighbors.push_back(neighbor);
            } else {
                free_BFT_kmer(neighbor, 1);
            }
        }
    }
    free(neighborKmer);
    return neighbors;
}

bool Graph::hasSuffixNeighbors(BFT_kmer* bftKmer) const {
    return getNumSuffixNeighbors(bftKmer) > 0;
}

uint32_t Graph::getNumSuffixNeighbors(BFT_kmer* bftKmer) const {
    vector<BFT_kmer*> neighbors = getSuffixNeighbors(bftKmer->kmer);
    uint32_t numNeighbors = neighbors.size();
    freeBFTKmers(neighbors);
    return numNeighbors;
}

BFT_kmer* Graph::getPrefixNeighbors(BFT_kmer* bftKmer) const {
    if(is_kmer_in_cdbg(bftKmer)) {
        return get_predecessors(bftKmer, bft);
    }
    return NULL;
}

vector<BFT_kmer*> Graph::getPrefixNeighbors(char* kmer) const {
    vector<BFT_kmer*> neighbors;
    uint32_t len = strlen(kmer);
    char* neighborKmer = (char*) malloc(len + 1);
    memcpy(neighborKmer + 1, kmer, (len - 1) * sizeof(char));
    for(int i = 0; i < 4; i++) {
        switch(i) {
            case 0: neighborKmer[0] = 'A'; break;
            case 1: neighborKmer[0] = 'C'; break;
            case 2: neighborKmer[0] = 'G'; break;
            case 3: neighborKmer[0] = 'T'; break;
        }
        BFT_kmer* neighbor = getBFTKmer(neighborKmer);
        if(neighbor != NULL) {
            if(isValidBFTKmer(neighbor)) {
                neighbors.push_back(neighbor);
            } else {
                free_BFT_kmer(neighbor, 1);
            }
        }
    }
    free(neighborKmer);
    return neighbors;
}

bool Graph::hasPrefixNeighbors(BFT_kmer* bftKmer) const {
    return getNumPrefixNeighbors(bftKmer) > 0;
}

uint32_t Graph::getNumPrefixNeighbors(BFT_kmer *bftKmer) const {
    vector<BFT_kmer*> neighbors = getPrefixNeighbors(bftKmer->kmer);
    uint32_t numNeighbors = neighbors.size();
    freeBFTKmers(neighbors);
    return numNeighbors;
}

void Graph::freeBFTKmers(vector<BFT_kmer*> kmers) const {
    for(auto const& kmer : kmers) {
        free_BFT_kmer(kmer, 1);
    }
}

uint32_t Graph::getKmerSize() const {
    return bft->k;
}

bool Graph::checkIfEmpty(BFT_kmer* bftKmers) const {
    for(uint32_t i = 0; i < 4; i++) {
        if(isValidBFTKmer(bftKmers + i)) {
            return false;
        }
    }
    return true;
}
