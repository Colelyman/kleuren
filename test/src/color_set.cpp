/*
 * Test cases for ColorSet.
 */

#include "catch.hpp"

#include "color_set.h"

TEST_CASE("ColorSet tests", "[colors]") {
    string pathToFMIndex1 = "./data/zika.bwtdisk";
    string pathToFMIndex2 = "./data/toy1.bwtdisk";
    string pathToFMIndex3 = "./data/toy2.bwtdisk";
    shared_ptr<Color> color1(new Color(1, "zika", pathToFMIndex1));
    shared_ptr<Color> color2(new Color(2, "toy1", pathToFMIndex2));
    shared_ptr<Color> color3(new Color(3, "toy2", pathToFMIndex3));

    ColorSet colors = ColorSet(set<shared_ptr<Color> >({color1, color2, color3}));

    SECTION("Testing allContainsKmer") {
        string kmer1 = "AAA";
        REQUIRE(colors.allContainsKmer(kmer1));
        string kmer2 = "AAAAAAAAA";
        REQUIRE(!colors.allContainsKmer(kmer2));
        string kmer3 = "GAA";
        REQUIRE(!colors.allContainsKmer(kmer3));
        string kmer4 = "ATA";
        REQUIRE(!colors.allContainsKmer(kmer4));
    }
}
