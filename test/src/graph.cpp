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
    strcpy(fileName, "./data/bft.out");
    Graph graph = Graph(fileName);

    SECTION("Testing general color related functions in the Graph") {
        REQUIRE(graph.getNumColors() == 4);
        REQUIRE(strcmp(graph.getColorFilePath(0), "ebola.kmers.txt") == 0);
        REQUIRE(strcmp(graph.getColorFilePath(1), "zika.kmers.txt") == 0);
        REQUIRE(strcmp(graph.getColorFilePath(2), "flu.kmers.txt") == 0);
        REQUIRE(strcmp(graph.getColorFilePath(3), "marburg.kmers.txt") == 0);
    }

    SECTION("Testing BFTKmer contains/validity methods") {
        BFT_kmer* bftKmer = NULL;
        REQUIRE(!graph.isValidBFTKmer(bftKmer));

        char* kmer = (char*) malloc(19);
        strcpy(kmer, "AAAAAACATTAAGAGAAC");
        REQUIRE(graph.isBFTKmer(kmer));
        bftKmer = graph.getBFTKmer(kmer);
        REQUIRE(bftKmer != NULL);
        REQUIRE(graph.isValidBFTKmer(bftKmer));
        free(bftKmer);

        strcpy(kmer, "AAAAAAAAAAAAAAAAAA");
        REQUIRE(!graph.isBFTKmer(kmer));
        bftKmer = graph.getBFTKmer(kmer);
        REQUIRE(bftKmer == NULL);
        REQUIRE(!graph.isValidBFTKmer(bftKmer));
        // don't free bftKmer here because it should be NULL

        free(kmer);
    }

    SECTION("Testing the BFTKmer color functions of the Graph") {
        char* kmer = (char*) malloc(19);
        strcpy(kmer, "AAAAAACATTAAGAGAAC");
        BFT_kmer* bftKmer = graph.getBFTKmer(kmer);

        REQUIRE(graph.getNumColors(bftKmer) == 1);

        REQUIRE(graph.getColors(bftKmer)[0] == 1);
        REQUIRE(graph.getColors(bftKmer)[1] == 0);

        free(kmer);
        free(bftKmer);
    }

    SECTION("Testing the get neighbor methods of the Graph") {
        char* kmer = (char*) malloc(19);
        strcpy(kmer, "AAAAAACATTAAGAGAAC");
        BFT_kmer* bftKmer = graph.getBFTKmer(kmer);
        BFT_kmer* neighbors = graph.getSuffixNeighbors(bftKmer);
        REQUIRE(graph.isValidBFTKmer(neighbors + 0));
        REQUIRE(!graph.isValidBFTKmer(neighbors + 1));
        REQUIRE(!graph.isValidBFTKmer(neighbors + 2));
        REQUIRE(!graph.isValidBFTKmer(neighbors + 3));
        REQUIRE(graph.hasSuffixNeighbors(bftKmer));

        free_BFT_kmer(neighbors, 4);
        free_BFT_kmer(bftKmer, 1);

        strcpy(kmer, "TTTCTTAATCTTCATCAA");
        REQUIRE(graph.isBFTKmer(kmer));
        strcpy(kmer, "TTTCTTAATCTTCATCAC");
        REQUIRE(graph.isBFTKmer(kmer));

        strcpy(kmer, "TTTTCTTAATCTTCATCA");
        bftKmer = graph.getBFTKmer(kmer);
        neighbors = graph.getSuffixNeighbors(bftKmer);
        REQUIRE(graph.isValidBFTKmer(neighbors + 0));
        REQUIRE(graph.isValidBFTKmer(neighbors + 1));
        REQUIRE(!graph.isValidBFTKmer(neighbors + 2));
        REQUIRE(!graph.isValidBFTKmer(neighbors + 3));
        REQUIRE(graph.hasSuffixNeighbors(bftKmer));

        free_BFT_kmer(neighbors, 4);
        free_BFT_kmer(bftKmer, 1);

        strcpy(kmer, "AAAAACATTAAGAGAACA");
        bftKmer = graph.getBFTKmer(kmer);
        neighbors = graph.getPrefixNeighbors(bftKmer);
        REQUIRE(graph.isValidBFTKmer(neighbors + 0));
        REQUIRE(graph.hasPrefixNeighbors(bftKmer));

        free_BFT_kmer(neighbors, 4);
        free_BFT_kmer(bftKmer, 1);

        free(kmer);
    }


}
