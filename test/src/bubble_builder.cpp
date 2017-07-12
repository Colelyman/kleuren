/*
 * Test cases for BubbleBuilder.
 */

#include "catch.hpp"

#include "bubble_builder.h"

TEST_CASE("BubbleBuilder findEndKmer", "[bubble]") {
    BubbleBuilder bb = BubbleBuilder();
    string pathToToy1 = "./data/toy1.bwtdisk";
    string pathToToy2 = "./data/toy2.bwtdisk";
    string pathToToy3 = "./data/toy3.bwtdisk";
    string pathToToy4 = "./data/toy4.bwtdisk";
    Color toyColor1 = Color(1, "toyColor1", pathToToy1);
    Color toyColor2 = Color(2, "toyColor2", pathToToy2);
    Color toyColor3 = Color(3, "toyColor3", pathToToy3);
    Color toyColor4 = Color(4, "toyColor4", pathToToy4);

    ColorSet colors = ColorSet(set<Color*>({&toyColor1, &toyColor2}));

    SECTION("Finding a simple endKmer of two colors with a single SNP, that turns out to be a loop") {
        string startKmer = "AAA";
        string endKmer = "AAA";
        REQUIRE(bb.findEndKmer(startKmer, &toyColor1, colors) == endKmer);
        REQUIRE(bb.findEndKmer(startKmer, &toyColor2, colors) == endKmer);
    }

    SECTION("Finding the endKmer between toy 3 and toy 4 colors") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        ColorSet colors = ColorSet(set<Color*>({&toyColor3, &toyColor4}));
        REQUIRE(bb.findEndKmer(startKmer, &toyColor3, colors) == endKmer);
        REQUIRE(bb.findEndKmer(startKmer, &toyColor4, colors) == endKmer);
    }

    SECTION("Extending a simple linear path") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        string path3 = "CTGCAAT";
        REQUIRE(bb.extendPath(startKmer, endKmer, &toyColor3, 10) == path3);
    }

    SECTION("Extending a simple branching path") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        string path4 = "CTGAAAT";
        REQUIRE(bb.extendPath(startKmer, endKmer, &toyColor4, 10) ==  path4);
    }

}
