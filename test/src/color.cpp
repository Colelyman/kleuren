/*
 * Test cases for Color.
 */

#include "catch.hpp"

#include "color.h"

using namespace Catch::Matchers;

TEST_CASE("Color operations", "[color]") {
    string pathToFMIndex = "./data/zika.bwtdisk";
    Color testColor1 = Color(0, "testColor1", pathToFMIndex);

    SECTION("Data member testing") { 
        REQUIRE(testColor1.getName() == "testColor1");
        REQUIRE(testColor1.getID() == 0);
    }

    SECTION("Vertex membership testing") {
        string vertex1 = "GGGTTTGGAGTCTTCCACACCAGT";
        REQUIRE(testColor1.isVertex(vertex1));

        string vertex2 = "TTTGGGGATTCTTACATTGTCATAGGAGTTGGGGACAAGAAAATCACCCACCACTGGCATAGG";
        REQUIRE(testColor1.isVertex(vertex2));

        string vertex3 = "AAAAAAA";
        REQUIRE(!testColor1.isVertex(vertex3));
    }

    SECTION("Neighbor testing") {
        string neighborVertex1 = "TGGCCATTTGAAATGCCGC";
        string prefix1 = neighborVertex1.substr(1);
        REQUIRE(testColor1.isPrefixNeighbor(prefix1, 'T'));
        REQUIRE(!testColor1.isPrefixNeighbor(prefix1, 'A'));

        string suffix1 = neighborVertex1.substr(0, neighborVertex1.length() - 1);
        REQUIRE(testColor1.isSuffixNeighbor(suffix1, 'C'));
        REQUIRE(!testColor1.isSuffixNeighbor(suffix1, 'T'));

        /// @todo test getting Suffix and Prefix neighbors
        
        neighborVertex1 = neighborVertex1.substr(1, neighborVertex1.length() - 1);
        //CHECK_THAT(testColor1.getSuffixNeighbors(neighborVertex1), VectorContains("C"));
        //CHECK_THAT(testColor1.getPrefixNeighbors(neighborVertex1), VectorContains("T"));
    }

}
