#include "abstract_graph.h"

AbstractGraph::AbstractGraph(Graph* graph) {
    this->graph = graph;
}

AbstractGraph::AbstractNode::AbstractNode(string seq, uint32_t id, uint32_t* colors) {
    this->seq = seq;
    this->id = id;
    uint32_t size = colors[0] + 1;
    this->colors = (uint32_t*) malloc(size * sizeof(uint32_t));
    memcpy(this->colors, colors, size);
}

AbstractGraph::AbstractNode::AbstractNode(const AbstractNode& o) {
    this->seq = o.seq;
    this->id = o.id;
    uint32_t size = o.colors[0] + 1;
    this->colors = (uint32_t*) malloc(size * sizeof(uint32_t));
    memcpy(this->colors, o.colors, size);
}

AbstractGraph::AbstractNode::AbstractNode(AbstractNode&& o) noexcept {
    this->seq = std::move(o.seq);
    this->id = std::move(o.id);
    this->colors = std::move(o.colors);
}

AbstractGraph::AbstractNode::~AbstractNode() noexcept {
    free(colors);
}

void AbstractGraph::AbstractNode::appendToSeq(const char c) {
    seq.append(1, c);
}

string AbstractGraph::AbstractNode::getSeq() {
    return seq;
}

uint32_t AbstractGraph::AbstractNode::getId() {
    return id;
}

uint32_t* AbstractGraph::AbstractNode::getColors() {
    return colors;
}

void AbstractGraph::construct(BFT_kmer* startKmer) {
    uint32_t currentId = 0;
}

string AbstractGraph::getDependencies() {
    return "";
}

string AbstractGraph::doTopologicalOrdering(string dependencies) {

    return "";
}
