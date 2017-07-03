/*
 * Test cases for BubbleBuilder.
 */

#include "catch.hpp"

#include "bubble_builder.h"

TEST_CASE("BubbleBuilder findEndKmer", "[bubble]") {
    BubbleBuilder bb = BubbleBuilder();
    string pathToToy1 = "./data/toy1.bwtdisk";
    string pathtoToy2 = "./data/toy2.bwtdisk";
    Color toyColor1 = Color(1, "toyColor1", pathToToy1);
    Color toyColor2 = Color(2, "toyColor2", pathToToy2);

    ColorSet colors = ColorSet(set<Color*>({&toyColor1, &toyColor2});

    SECTION("Finding a simple endKmer of two colors with a single SNP") {
        string startKmer = "ACT";
        string endKmer = "TAC";
        REQUIRE(strcmp(bb.findEndKmer(startKmer, color, colors), endKmer) == 0);
    }
}
