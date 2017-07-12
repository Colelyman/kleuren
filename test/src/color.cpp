/*
 * Test cases for Color.
 */

#include "catch.hpp"

#include "color.h"

TEST_CASE("Color operations", "[color]") {
    string pathToFMIndex = "./data/zika.bwtdisk";
    Color zikaColor = Color(1, "zikaColor", pathToFMIndex);

    SECTION("Data member testing") { 
        REQUIRE(zikaColor.getName() == "zikaColor");
        REQUIRE(zikaColor.getID() == 1);
    }

    SECTION("Vertex membership testing") {
        string vertex1 = "GGGTTTGGAGTCTTCCACACCAGT";
        REQUIRE(zikaColor.isVertex(vertex1));

        string vertex2 = "TTTGGGGATTCTTACATTGTCATAGGAGTTGGGGACAAGAAAATCACCCACCACTGGCATAGG";
        REQUIRE(zikaColor.isVertex(vertex2));

        string vertex3 = "AAAAAAA";
        REQUIRE(!zikaColor.isVertex(vertex3));
    }

    SECTION("Single neighbor testing") {
        string neighborVertex1 = "TGGCCATTTGAAATGCCGC";
        string prefix1 = neighborVertex1.substr(1);
        REQUIRE(zikaColor.isPrefixNeighbor(prefix1, 'T'));
        REQUIRE(!zikaColor.isPrefixNeighbor(prefix1, 'A'));

        string suffix1 = neighborVertex1.substr(0, neighborVertex1.length() - 1);
        REQUIRE(zikaColor.isSuffixNeighbor(suffix1, 'C'));
        REQUIRE(!zikaColor.isSuffixNeighbor(suffix1, 'T'));

        neighborVertex1 = neighborVertex1.substr(1, neighborVertex1.length() - 2);
        vector<string> suffixNeighbors = {"GCCATTTGAAATGCCGC"};
        REQUIRE(zikaColor.getSuffixNeighbors(neighborVertex1) == suffixNeighbors);

        vector<string> prefixNeighbors = {"TGGCCATTTGAAATGCC"};
        REQUIRE(zikaColor.getPrefixNeighbors(neighborVertex1) == prefixNeighbors);
    }

    SECTION("Multiple neighbor testing") {
        string neighborVertex2 = "ACCAAG";
        vector<string> neighbors = {"CCAAGA", "CCAAGC", "CCAAGG", "CCAAGT"};
        REQUIRE(zikaColor.getSuffixNeighbors(neighborVertex2) == neighbors);
    }

    SECTION("Neighbor testing with small dataset") {
        Color toy4Color = Color(2, "toy4", "./data/toy4.bwtdisk");
        string vertex = "CTG";
        vector<string> neighbors = {"TGA"};
        REQUIRE(toy4Color.getSuffixNeighbors(vertex) == neighbors);
        
        vertex = "TGA";
        neighbors = {"GAA"};
        REQUIRE(toy4Color.getSuffixNeighbors(vertex) == neighbors);

        vertex = "GAA";
        neighbors = {"AAA", "AAT"};
        REQUIRE(toy4Color.getSuffixNeighbors(vertex) == neighbors);

        vertex = "AAA";
        neighbors = {"AAA", "AAT"};
        REQUIRE(toy4Color.getSuffixNeighbors(vertex) == neighbors);

        vertex = "ATT";
        // this is because of reverse complement!!
        REQUIRE(toy4Color.isVertex(vertex));

        vertex = "AAT";
        neighbors = {"ATT"};
        // ATT is a neighbor of AAT because the reverse complement of AAT is TTA, and 
        // the reverse complement of AAT is ATT
        REQUIRE(toy4Color.getSuffixNeighbors(vertex) == neighbors);
    }

}
