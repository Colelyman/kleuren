/*
 * Test cases for ColorManager.
 */

#include "catch.hpp"

#include "color_manager.h"
#include "graph_builder.h"

TEST_CASE("ColorManager testing", "[color]") {
    string pathToColorFile = "./data/viruses.colors.txt";
    ifstream colorFile;
    colorFile.open(pathToColorFile);
    Graph graph = Graph();
    GraphBuilder graphBuilder = GraphBuilder(&graph, 17);
    ColorManager colorManager = ColorManager(&colorFile, &graphBuilder);

    SECTION("Add colors testing and getColor testing") {
        colorManager.addColors();
        REQUIRE(colorManager.getColor(0)->getName() == "Ebola");
        REQUIRE(colorManager.getColor(1)->getName() == "Flu");
        REQUIRE(colorManager.getColor(2)->getName() == "Marburg");
        REQUIRE(colorManager.getColor(3)->getName() == "Zika");
    }

    colorFile.close();
}
