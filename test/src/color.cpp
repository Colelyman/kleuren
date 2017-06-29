/*
 * Test cases for Color.
 */

#include "catch.hpp"

#include "color.h"
#include "fm_index.h"

TEST_CASE("FMIndex and Color operations", "[color][fm_index]") {
    string pathToFMIndex = "../data/testGenome.bwtdisk";
    FMIndex index(pathToFMIndex, 256);
    Color testColor1 = Color(0, "testColor1", pathToFMIndex);

    //REQUIRE(testColor1.getName() == "testColor1");
    //REQUIRE(testColor1.getID() == 0);
}
