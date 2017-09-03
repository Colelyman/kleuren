/*
 * Test cases for ColorManager.
 */

#include "catch.hpp"

#include "color_manager.h"

TEST_CASE("ColorManager testing", "[color]") {
    string pathToColorFile = "./data/viruses.colors.txt";
    ifstream colorFile;
    colorFile.open(pathToColorFile);
    ColorManager colorManager = ColorManager(&colorFile);

    SECTION("Add colors testing and getColor testing") {
        colorManager.addColors();
        REQUIRE(colorManager.getColor(0)->getName() == "Ebola");
        REQUIRE(colorManager.getColor(1)->getName() == "Flu");
        REQUIRE(colorManager.getColor(2)->getName() == "Marburg");
        REQUIRE(colorManager.getColor(3)->getName() == "Zika");
    }

    colorFile.close();
}
