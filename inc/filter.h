/**
 * @class Filter
 *
 * This is a class that will filter BFTKmers.
 *
 * @author Cole Lyman
 *
 * @date 2018/5/22
 *
 */

#ifndef FILTER_H
#define FILTER_H

#include "graph.h"
#include "bubble_stats.h"

class Filter {
    public:
        Filter(Graph* graph);

        bool filterStart(BFT_kmer* bftKmer, uint32_t n, BubbleStats* bubbleStats);

        bool filterEnd(BFT_kmer* bftKmer, uint32_t n, BubbleStats* bubbleStats);

        bool filterMiddle(BFT_kmer* bftKmer, BubbleStats* bubbleStats);

    private:
        Graph* graph;
};

#endif // FILTER_H
