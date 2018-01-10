/*
 * Implementation of graph.h.
 */

#include "graph.h"

Graph::Graph(char* bftFileName) {
    bft = load_BFT(bftFileName);
    free(bftFileName);
}

Graph::~Graph() {
    free_cdbg(bft);
}

bool Graph::isBFTKmer(char* strKmer) const {
    if(query_sequence(bft, strKmer, 0.001, false)) {
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

uint32_t Graph::getNumColors(BFT_kmer* bftKmer) const {
    uint32_t numColors = 0;
    BFT_annotation* bftAnno = get_annotation(bftKmer);
    uint32_t* temp = get_list_id_genomes(bftAnno, bft);
    numColors = temp[0];
    free(bftAnno);
    free(temp);

    return numColors;
}

int Graph::getNumColors() const {
    return bft->nb_genomes;
}

uint32_t* Graph::getColors(BFT_kmer* bftKmer) const {
    BFT_annotation* bftAnno = get_annotation(bftKmer);

    return get_list_id_genomes(bftAnno, bft);
}

BFT_kmer* Graph::getSuffixNeighbors(BFT_kmer* bftKmer) const {
    if(is_kmer_in_cdbg(bftKmer)) {
        return get_successors(bftKmer, bft);
    }
    return NULL;
}

bool Graph::hasSuffixNeighbors(BFT_kmer* bftKmer) const {
    return checkIfEmpty(getSuffixNeighbors(bftKmer));
}

BFT_kmer* Graph::getPrefixNeighbors(BFT_kmer* bftKmer) const {
    return get_predecessors(bftKmer, bft);
}

bool Graph::hasPrefixNeighbors(BFT_kmer* bftKmer) const {
    return checkIfEmpty(getPrefixNeighbors(bftKmer));
}

bool Graph::checkIfEmpty(BFT_kmer* bftKmers) const {
    for(uint32_t i = 0; i < 4; i++) {
        if(isValidBFTKmer(bftKmers + i)) {
            return false;
        }
    }
    return true;
}
