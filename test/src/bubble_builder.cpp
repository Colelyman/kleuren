/*
 * Test cases for BubbleBuilder.
 */

#include "catch.hpp"

#include "bubble_builder.h"

TEST_CASE("BubbleBuilder findEndKmer", "[bubble]") {
    BubbleBuilder bb = BubbleBuilder();
    string pathToToy1 = "./data/toy1.bwtdisk";
    string pathToToy2 = "./data/toy2.bwtdisk";
    Color toyColor1 = Color(1, "toyColor1", pathToToy1);
    Color toyColor2 = Color(2, "toyColor2", pathToToy2);

    ColorSet colors = ColorSet(set<Color*>({&toyColor1, &toyColor2}));

    SECTION("Finding a simple endKmer of two colors with a single SNP") {
        string startKmer = "ACT";
        const char* endKmer = "TAC";
        REQUIRE(strcmp(bb.findEndKmer(startKmer, &toyColor1, colors).c_str(), endKmer) == 0);
        REQUIRE(strcmp(bb.findEndKmer(startKmer, &toyColor2, colors).c_str(), endKmer) == 0);
    }
}
