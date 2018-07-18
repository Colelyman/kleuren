/*
 * Implementation of bubble_stats.h
 */

#include "bubble_stats.h"

#include <numeric>
#include <utility>

#define inc(var, num) var += num; return var;

using std::accumulate;
using std::pair;

BubbleStats::BubbleStats() {
   numVisitedNodes = 0;
   numKmers = 0;
   numNoEndKmersFound = 0;
   numNoPathsFound = 0;
   numBubblesFound = 0;
}

string BubbleStats::toString() {
    stringstream ss;
    ss << "Bubble statistics" <<
        "\n\tNumber of kmers: " << numKmers <<
        "\n\tNumber of nodes visited: " << numVisitedNodes <<
        "\n\tNumber of nodes given for each color\n\tColor\t\tNumber of nodes\tPercentage";
    uint32_t totalVisited = accumulate(numColorsInNodes.begin(), numColorsInNodes.end(), 0,
                                       [](const uint32_t previous, const pair<uint32_t, uint32_t>& p)
                                       { return previous + p.second; });
    for(const auto& color : numColorsInNodes) {
        ss << "\n\t" << color.first <<
            "\t\t" << color.second <<
            "\t" << (float) color.second / totalVisited;
    }

    ss << "\n\tNumber of bubbles where no end kmer was found: " << numNoEndKmersFound;
    ss << "\n\tNumber of bubbles where no path was found: " << numNoPathsFound;
    ss << "\n\tNumber of bubbles found: " << numBubblesFound;

    return ss.str();
}

uint32_t BubbleStats::incNumVisitedNodes(uint32_t num) {
    inc(numVisitedNodes, num)
}

uint32_t BubbleStats::incNumKmers(uint32_t num) {
    inc(numKmers, num)
}

uint32_t BubbleStats::incNumNoEndKmersFound(uint32_t num) {
    inc(numNoEndKmersFound, num)
}

uint32_t BubbleStats::incNumNoPathsFound(uint32_t num) {
    inc(numNoPathsFound, num)
}

uint32_t BubbleStats::incNumBubblesFound(uint32_t num) {
    inc(numBubblesFound, num)
}

uint32_t BubbleStats::incNumColorsInNodes(uint32_t color, uint32_t num) {
    inc(numColorsInNodes[color], num)
}
