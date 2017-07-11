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

    ColorSet colors = ColorSet(set<Color*>({&toyColor1, &toyColor2}));

    SECTION("Finding a simple endKmer of two colors with a single SNP, that turns out to be a loop") {
        string startKmer = "AAA";
        const char* endKmer = "AAA";
        REQUIRE(strcmp(bb.findEndKmer(startKmer, &toyColor1, colors).c_str(), endKmer) == 0);
        REQUIRE(strcmp(bb.findEndKmer(startKmer, &toyColor2, colors).c_str(), endKmer) == 0);
    }

    SECTION("Extending a simple linear path") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        string path3 = "CTGCAAT";
        Color toyColor3 = Color(3, "toyColor3", pathToToy3);
        CHECK(bb.extendPath(startKmer, endKmer, &toyColor3, 10) == path3);
    }

    SECTION("Extending a path with a loop in it") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        string path4 = "CTGAAAT";
        Color toyColor4 = Color(4, "toyColor4", pathToToy4);
        CHECK(bb.extendPath(startKmer, endKmer, &toyColor4, 10) ==  path4);
    }
}
