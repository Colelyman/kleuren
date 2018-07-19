/*
 * Test cases for BubbleBuilder.
 */

#include "catch.hpp"

#include "bubble_builder.h"

#include <map>

using std::map;

TEST_CASE("BubbleBuilder testing", "[bubble]") {
    char* graphPath = (char*) malloc(64 * sizeof(char*));
    strcpy(graphPath, "./data/small/bft.out");
    Graph* graph = new Graph(graphPath);
    BubbleStats* bubbleStats = new BubbleStats();
    BubbleBuilder* bubbleBuilder = new BubbleBuilder(graph, bubbleStats);

    SECTION("Testing finding an end kmer") {
        char* kmer = (char*) malloc(10);
        strcpy(kmer, "GGCTAACAC");
        BFT_kmer* startBFTKmer = graph->getBFTKmer(kmer);
        BFT_kmer* endBFTKmer = bubbleBuilder->findEndBFTKmer(startBFTKmer, 4, 30, 0);
        REQUIRE(strcmp(endBFTKmer->kmer, "GCTCAGGAC") == 0);

        free(kmer);
        free_BFT_kmer(startBFTKmer, 1);
        free_BFT_kmer(endBFTKmer, 1);
    }

    SECTION("Test extending the pahts") {
        char* startKmer = (char*) malloc(10);
        strcpy(startKmer, "GGCTAACAC");
        BFT_kmer* startBFTKmer = graph->getBFTKmer(startKmer);

        char* endKmer = (char*) malloc(10);
        strcpy(endKmer, "GCTCAGGAC");
        BFT_kmer* endBFTKmer = graph->getBFTKmer(endKmer);

        Bubble bubble = bubbleBuilder->extendPaths(startBFTKmer, endBFTKmer, 60);
        REQUIRE(bubble.isValid(9, 4));

        free_BFT_kmer(startBFTKmer, 1);
        free_BFT_kmer(endBFTKmer, 1);
        free(startKmer);
        free(endKmer);
    }

    SECTION("Test recursiveExtend on a single path") {
        char* startKmer = (char*) malloc(10);
        strcpy(startKmer, "GGCTAACAC");
        BFT_kmer* startBFTKmer = graph->getBFTKmer(startKmer);

        char* endKmer = (char*) malloc(10);
        strcpy(endKmer, "GCTCAGGAC");
        BFT_kmer* endBFTKmer = graph->getBFTKmer(endKmer);

        uint32_t* colors = graph->getColors(startBFTKmer);
        string path(startBFTKmer->kmer);
        REQUIRE(bubbleBuilder->recursiveExtend(startBFTKmer, 3, colors, endBFTKmer, path, 0, 30));
        REQUIRE(path == "GGCTAACACTTGAGCTCAGGAC");
        REQUIRE(colors[0] == 1);
        free(colors);

        free(startKmer);
        free_BFT_kmer(startBFTKmer, 1);
        free(endKmer);
        free_BFT_kmer(endBFTKmer, 1);
    }

    SECTION("Test recursiveExtend on multiple paths") {
        char* startKmer = (char*) malloc(10);
        strcpy(startKmer, "GGCTAACAC");
        BFT_kmer* startBFTKmer = graph->getBFTKmer(startKmer);

        char* endKmer = (char*) malloc(10);
        strcpy(endKmer, "GCTCAGGAC");
        BFT_kmer* endBFTKmer = graph->getBFTKmer(endKmer);

        map<uint32_t, string> paths = {{0, "GGCTAACACATGAGCTCAGGAC"},
                                       {1, "GGCTAACACTTGTGCTCAGGAC"},
                                       {2, "GGCTAACACCTGAGCTCAGGAC"},
                                       {3, "GGCTAACACTTGAGCTCAGGAC"}};
        for(uint32_t i = 0; i < 4; i++) {
            uint32_t* colors = graph->getColors(startBFTKmer);
            string path(startBFTKmer->kmer);
            REQUIRE(bubbleBuilder->recursiveExtend(startBFTKmer, i, colors, endBFTKmer, path, 0, 30));
            REQUIRE(path == paths[i]);
            free(colors);
        }
        free(startKmer);
        free_BFT_kmer(startBFTKmer, 1);
        free(endKmer);
        free_BFT_kmer(endBFTKmer, 1);
    }

    delete graphPath;
    delete graph;
    delete bubbleStats;
    delete bubbleBuilder;
}
