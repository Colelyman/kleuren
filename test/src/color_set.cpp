/*
 * Test cases for ColorSet.
 */

#include "catch.hpp"

#include "color_set.h"

using std::make_shared;

TEST_CASE("ColorSet tests", "[colors]") {
    string pathToFMIndex1 = "./data/zika.bwtdisk";
    string pathToFMIndex2 = "./data/toy1.bwtdisk";
    string pathToFMIndex3 = "./data/toy2.bwtdisk";
    Color color1 = Color(1, "zika", pathToFMIndex1);
    Color color2 = Color(2, "toy1", pathToFMIndex2);
    Color color3 = Color(3, "toy2", pathToFMIndex3);

    ColorSet colors = ColorSet(set<shared_ptr<Color> >({make_shared<Color>(color1), make_shared<Color>(color2), make_shared<Color>(color3)}));

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
