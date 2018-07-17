/*
 * Test cases for Graph.
 */

#include "catch.hpp"
#include <iostream>

#include "graph.h"

using std::cout;
using std::endl;

TEST_CASE("Graph loading and basic utilities", "[graph]") {
    char* fileName = (char*) malloc(64 * sizeof(char));
    strcpy(fileName, "./data/small/bft.out");
    Graph graph = Graph(fileName);

    SECTION("Testing general color related functions in the Graph") {
        REQUIRE(graph.getNumColors() == 4);
        REQUIRE(strcmp(graph.getColorFilePath(0), "1.kmers.txt") == 0);
        REQUIRE(strcmp(graph.getColorFilePath(1), "2.kmers.txt") == 0);
        REQUIRE(strcmp(graph.getColorFilePath(2), "3.kmers.txt") == 0);
        REQUIRE(strcmp(graph.getColorFilePath(3), "4.kmers.txt") == 0);
    }

    SECTION("Testing BFTKmer contains/validity methods") {
        BFT_kmer* bftKmer = NULL;
        REQUIRE(!graph.isValidBFTKmer(bftKmer));

        char* kmer = (char*) malloc(10);
        strcpy(kmer, "ACTTGTGCT");
        REQUIRE(graph.isBFTKmer(kmer));
        bftKmer = graph.getBFTKmer(kmer);
        REQUIRE(bftKmer != NULL);
        REQUIRE(graph.isValidBFTKmer(bftKmer));
        free_BFT_kmer(bftKmer, 1);

        strcpy(kmer, "AAAAAAAAA");
        REQUIRE(!graph.isBFTKmer(kmer));
        bftKmer = graph.getBFTKmer(kmer);
        REQUIRE(bftKmer == NULL);
        REQUIRE(!graph.isValidBFTKmer(bftKmer));
        // don't free bftKmer here because it should be NULL

        free(kmer);
    }

    SECTION("Testing the BFTKmer color functions of the Graph") {
        char* kmer = (char*) malloc(10);
        strcpy(kmer, "CATGAGCTC");
        BFT_kmer* bftKmer = graph.getBFTKmer(kmer);

        REQUIRE(graph.getNumColors(bftKmer) == 1);

        REQUIRE(graph.getColors(bftKmer)[0] == 1); // the number of colors
        REQUIRE(graph.getColors(bftKmer)[1] == 0); // the color id

        free(kmer);
        free_BFT_kmer(bftKmer, 1);
    }

    SECTION("Testing getting the colors of a kmer multiple times") {
        char* kmer = (char*) malloc(10);
        strcpy(kmer, "GGCTAACAC");
        BFT_kmer* bftKmer = graph.getBFTKmer(kmer);

        int n = 10;
        for(int i = 0; i < n; i++) {
            REQUIRE(graph.getNumColors(bftKmer) == 4);
        }

        free(kmer);
        free_BFT_kmer(bftKmer, 1);
    }

    SECTION("Testing the get neighbor methods of the Graph") {
        char* kmer = (char*) malloc(9);
        strcpy(kmer, "GGCTAACAC");
        BFT_kmer* bftKmer = graph.getBFTKmer(kmer);
        BFT_kmer* neighbors = graph.getSuffixNeighbors(bftKmer);
        REQUIRE(graph.isValidBFTKmer(neighbors + 0));
        REQUIRE(graph.isValidBFTKmer(neighbors + 1));
        REQUIRE(!graph.isValidBFTKmer(neighbors + 2));
        REQUIRE(graph.isValidBFTKmer(neighbors + 3));
        REQUIRE(graph.hasSuffixNeighbors(bftKmer));

        free_BFT_kmer(neighbors, 4);
        free_BFT_kmer(bftKmer, 1);

        free(kmer);
    }


}
