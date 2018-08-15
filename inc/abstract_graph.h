/**
 * @class AbstractGraph
 *
 * Implementing an alternative to find bubbles. This is used to find bubbles
 * more efficiently.
 *
 * @author Cole Lyman
 *
 * @date 2018/8/13
 * 
 */

#ifndef ABSTRACT_GRAPH_H
#define ABSTRACT_GRAPH_H

#include <string>
#include <vector>
#include <sstream>
#include <sparsepp/spp.h>

#include "graph.h"

using std::string;
using std::vector;
using std::stringstream;
using spp::sparse_hash_map;

class AbstractGraph {

    public:

        AbstractGraph(Graph* graph);
        
        class AbstractNode {

            public:

                AbstractNode(string seq, uint32_t id, uint32_t* colors);

                AbstractNode(const AbstractNode& o);

                AbstractNode(AbstractNode&& o) noexcept;

                ~AbstractNode() noexcept;

                AbstractNode& operator=(const AbstractNode& o) {
                    AbstractNode tmp(o);
                    *this = std::move(tmp);
                    return *this;
                }

                AbstractNode& operator=(AbstractNode&& o) noexcept {
                    if(this == &o) {
                        return *this;
                    }
                    free(colors);
                    seq = o.seq;
                    id = o.id;
                    colors = o.colors;
                    o.colors = NULL;
                    return *this;
                }

                void appendToSeq(const char c);

                string getSeq();

                uint32_t getId();

                uint32_t* getColors();

            private:

                string seq;

                uint32_t id;

                uint32_t* colors;
        };

        /// This function will create the AbstractGraph starting with startKmer,
        /// which will essentially be the strongly connected component of
        /// startKmer. This will also unitig all of the edges.
        /// @param startKmer any kmer in the CdBG to start with.
        void construct(BFT_kmer* startKmer);

        string getDependencies();

        string doTopologicalOrdering(string dependencies);

    private:

        Graph* graph;
        
        sparse_hash_map<int, vector<AbstractNode>> nodes;
};

#endif // ABSTRACT_GRAPH_H
